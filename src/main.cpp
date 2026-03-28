#include <SFML/Audio.hpp>
#include <exception>

#include "Game.hpp"
#include "LiveAudio.hpp"
#include "Recorder.hpp"
#include "Vec2.hpp"

/* NOTE::
 * GameEngine
 *		Scene
 *			Systems
 *			EntityManager
 *				Entity
 *					Componnent
 */

void test(void) {
	sf::SoundBufferRecorder recorder;
	// Recorder recorder;
	auto devices = recorder.getAvailableDevices();
	for (const auto &e : devices)
		std::cout << e << std::endl;
	bool	 nothing = recorder.setDevice(devices[0]);
	sf::Time time = sf::milliseconds(2000);
	while (true) {
		if (recorder.start()) {
			sf::sleep(time);
			recorder.stop();
		}
		const sf::SoundBuffer buffer = recorder.getBuffer();
		sf::Sound			  test(buffer);
		test.play();
		sf::sleep(time);
	}
}

void LiveAudioTest(void) {
	LiveAudio liveAudio;
	std::cout << "Starting live microphone playback... (Watch out for audio "
				 "feedback/echo!)"
			  << std::endl;
	if (!liveAudio.startStream()) {
		return;
	}

	std::cout << "Press Enter to stop." << std::endl;
	std::cin.get();

	liveAudio.stopStream();
}

int main(void) {
	LiveAudioTest();
	// test();
	// sf::Music test("test.wav");
	// test.play();
	// test.setVolume(50);
	// while (true) {}
	// Game game("config.txt");
	// game.run();
}

// NOTE: Run game like this!
// int main(void) {
// 	Game game("config.txt");
// 	game.run();
// }

// void run(Engine &e) {
// 	while (e.window.isOpen()) {
// 		while (const std::optional event = e.window.pollEvent()) {
// 			if (event->is<sf::Event::Closed>())
// 				e.window.close();
// 			if (const auto *keyPressed =
// 					event->getIf<sf::Event::KeyPressed>()) {
// 				if (keyPressed->code == sf::Keyboard::Key::Escape)
// 					e.window.close();
// 			}
// 		}
// 		if (!e.window.isOpen()) {
// 			break;
// 		}
// 		e.window.clear();
// 		e.drawObjects();
// 		e.window.display();
// 	}
// }
//
// int main(int ac, char **av) {
// 	if (ac != 2) {
// 		std::cerr << "Please input config file\n";
// 		return (1);
// 	}
// 	try {
// 		Engine e(av[1]);
// 		run(e);
// 	} catch (std::exception &e) {
// 		std::cerr << e.what() << std::endl;
// 		return (1);
// 	}
// }
