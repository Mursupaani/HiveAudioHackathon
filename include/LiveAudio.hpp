#pragma once
#include <SFML/Audio.hpp>
#include "FastFourierTransform.hpp"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <vector>
#include <complex.h>

class LiveAudio : public sf::SoundStream {
	private:
		class LiveRecorder : public sf::SoundRecorder {
			private:
				LiveAudio &m_stream;

			public:
				LiveRecorder(LiveAudio &stream) : m_stream(stream) {}

			protected:
				bool onProcessSamples(const std::int16_t *samples,
									  std::size_t sampleCount) override {
					m_stream.receiveAudio(samples, sampleCount);
					return (true);
				}
		};
		std::mutex				  m_mutex;
		std::vector<std::int16_t> m_pendingSamples;
		std::vector<std::int16_t> m_playingSamples;
		std::complex<float>       m_freqs[SAMPLES];

	public:
		LiveRecorder recorder;
		LiveAudio() : recorder(*this) {}

		bool startStream(unsigned int sampleRate = 44100) {
			if (!sf::SoundRecorder::isAvailable()) {
				std::cerr << "Error: No audio capture device available"
						  << std::endl;
				return (false);
			}
			if (recorder.getDevice() == "") {
				auto devices = recorder.getAvailableDevices();
				for (auto &e : devices) {
					std::cout << e << std::endl;
				}
				if (!recorder.setDevice(devices[0])) {
					std::cerr << "Error: Failed to set device" << std::endl;
					return (false);
				}
			}
			if (!recorder.start(sampleRate)) {
				std::cerr << "Error: Failed to start the recorder" << std::endl;
				return (false);
			}
			initialize(1, sampleRate, {sf::SoundChannel::Mono});
			play();
			return (true);
		}

		void stopStream() {
			recorder.stop();
			stop();
		}

		std::complex<float>* getFreqs() {
		    return m_freqs;
		}

		void receiveAudio(const std::int16_t *samples,
						  std::size_t		  sampleCount) {
			std::lock_guard<std::mutex> lock(m_mutex);
			m_pendingSamples.insert(m_pendingSamples.end(), samples,
									samples + sampleCount);
			if (m_pendingSamples.size() > 22050) {
				m_pendingSamples.erase(m_pendingSamples.begin(),
									   m_pendingSamples.end() - 22050);
			}
			auto normalized = int16_normalize_float(samples);
			fft_ffs(normalized.data(), 1, m_freqs, sampleCount);
		}

		bool onGetData(Chunk &data) override {
			std::lock_guard<std::mutex> lock(m_mutex);
			if (m_pendingSamples.empty()) {
				m_playingSamples.assign(441, 0);
			} else {
				m_playingSamples.swap(m_pendingSamples);
				m_pendingSamples.clear();
			}
			data.samples = m_playingSamples.data();
			data.sampleCount = m_playingSamples.size();
			return (true);
		}
		void onSeek(sf::Time timeOffset) override {}
};
