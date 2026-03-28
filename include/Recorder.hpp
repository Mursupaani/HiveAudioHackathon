#pragma once
#include <SFML/Audio.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

class Recorder : public sf::SoundRecorder {
		std::vector<std::int16_t>
			m_samples;	//!< Temporary sample buffer to hold the recorded data
		sf::SoundBuffer
			m_buffer;  //!< Sound buffer that will contain the recorded data

		bool onStart() override	 // optional
		{
			// initialize whatever has to be done before the capture starts
			// std::cout << "record start\n";

			// return true to start the capture, or false to cancel it
			return true;
		}

		bool onProcessSamples(const std::int16_t *samples,
							  std::size_t		  sampleCount) override {
			// do something useful with the new chunk of samples
			// sf::SoundBuffer buffer(samples, sampleCount);
			// sf::Sound		sound(buffer);
			// sound.play();
			// sf::sleep(sf::milliseconds(200));
			// return true to continue the capture, or false to stop it
			auto channelMap = std::vector<sf::SoundChannel>{
				sf::SoundChannel::FrontLeft, sf::SoundChannel::FrontRight};
			m_buffer =
				sf::SoundBuffer(samples, sampleCount, 2, 44100, channelMap);
			sf::Sound sound(m_buffer);
			sound.play();
			sf::sleep(sf::milliseconds(100));
			std::cout << sampleCount << std::endl;
			// for (size_t i = 0; i < sampleCount; ++i) {
			// 	std::cout << samples[i] << std::endl;
			// }
			return true;
		}

		void onStop() override	// optional
		{
			// std::cout << "record stop\n";
			// clean up whatever has to be done after the capture is finished
		}

		// const sf::SoundBuffer &getBuffer() {
		// 	return ();
		// }
};
