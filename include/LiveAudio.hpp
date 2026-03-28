#pragma once
#include <SFML/Audio.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <vector>

// class LiveAudio : public sf::SoundStream {
// 	private:
// 		class LiveRecorder : public sf::SoundRecorder {
// 			private:
// 				LiveAudio &m_stream;
//
// 			public:
// 				LiveRecorder(LiveAudio &stream) : m_stream(stream) {}
//
// 			protected:
// 				bool onProcessSamples(const std::int16_t *samples,
// 									  std::size_t sampleCount) override {
// 					m_stream.receiveAudio(samples, sampleCount);
// 					return (true);
// 				}
// 		};
// 		LiveRecorder m_recorder;
// 		std::mutex	 m_mutex;
//
// 	public:
// 		LiveAudio() : m_recorder(*this) {}
//
// 		bool startStream(unsigned int sampleRate = 44100) {
// 			if (!sf::SoundRecorder::isAvailable()) {
// 				std::cerr << "Error: No audio capture device available"
// 						  << std::endl;
// 			}
// 			if (!m_recorder.start(sampleRate))
// 				std::cerr << "Error: Failed to start the recorder" << std::endl;
// 		initialize(unsigned int channelCount, unsigned int sampleRate, const
// std::vector<SoundChannel> &channelMap)
// 		}
// };
