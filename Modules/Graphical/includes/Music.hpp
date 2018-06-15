/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/
#pragma once

#include <SFML/Audio.hpp>
#include <map>

namespace Graphical {
	class Music {
	public:
		enum audioType {
			SOUND,
			MUSIC,
		};

		enum audioActionType {
			PLAY,
			STOP,
			//PAUSE,
		};
		Music() = default;
		~Music()
		{
			destroySounds();
			destroyMusics();
		};

		void soundManager(const audioActionType &action, const std::string &index)
		{
			switch (action) {
				case PLAY: playSound(index); break;
				case STOP: stopSound(index); break;
			//	case PAUSE: break;
				default: break;
			}
		}

		void musicManager(const audioActionType &action, const std::string &index)
		{
			switch (action) {
				case PLAY: playMusic(index); break;
				case STOP: stopMusic(index); break;
			//	case PAUSE: break;
				default: break;
			}
		}

		void audioManager()
		{
			for (auto &event : _events) {
				switch (event.audio) {
					case SOUND: soundManager(event.action, event.index); break;
					case MUSIC:	musicManager(event.action, event.index); break;
					default: break;
				}
			}
			_events.clear();
		}

		void addSoundBuffer(const std::string &index, const std::string &path)
		{
			std::unique_ptr<sf::SoundBuffer> buffer(std::make_unique<sf::SoundBuffer>());

			if (!buffer->loadFromFile(path))
				throw std::logic_error("Audio file: \'" + path + "\' not found");
			_buffers[index] = std::move(buffer);
		}

		void addSound(const std::string &index)
		{
			std::unique_ptr<sf::Sound> sound(std::make_unique<sf::Sound>());

			if (!_buffers[index])
				throw std::logic_error("Audio add sound: \'" + index + "\' not found");
			sound->setBuffer(*_buffers[index]);
			_sounds[index] = std::move(sound);
		}

		void createSound(const std::string &index, const std::string &path)
		{
			addSoundBuffer(index, _path + _sound + path);
			addSound(index);
		}

		void createMusic(const std::string &index, const std::string &path)
		{
			std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

			if (!music->openFromFile(_path + _music + path))
				throw std::logic_error("Audio create music: \'" + path + "\' not found");
			if (!_musics[index])
				_musics[index] = std::move(music);
		}

		void playSound(const std::string &index)
		{
			if (!_sounds[index])
				throw std::logic_error("Audio play sound: \'" + index + "\' not found");
			_sounds[index]->play();
		}


		void playMusic(const std::string &index)
		{
			if (!_musics[index])
				throw std::logic_error("Audio play music: \'" + index + "\' not found");
			_musics[index]->play();
			_musics[index]->setLoop(true);
		}

		void stopSound(const std::string &index)
		{
			if (!_sounds[index])
				throw std::logic_error("Audio stop sound: \'" + index + "\' not found");
			_sounds[index]->stop();
		}

		void stopMusic(const std::string &index)
		{
			if (!_musics[index])
				throw std::logic_error("Audio stop music: \'" + index + "\' not found");
			_musics[index]->stop();
		}

		void destroyMusics()
		{
			for (auto &music : _musics) {
				if (music.second->getStatus() == sf::Music::Status::Playing)
					music.second->stop();
			}
		}

		void destroySounds()
		{
			for (auto &sound : _sounds) {
				if (sound.second->getStatus() == sf::Sound::Status::Playing)
					sound.second->stop();
			}
		}

		void addEvent(const audioType &audio, const audioActionType &action, const std::string &index)
		{
			MusicEvent event;
			event.audio = audio;
			event.action = action;
			event.index = index;
			_events.emplace_back(event);
		}
	private:
		const std::string _path = "assets/audio/";
		const std::string _sound = "sounds/";
		const std::string _music = "musics/";
		std::map<std::string, std::unique_ptr<sf::SoundBuffer>> _buffers;
		std::map<std::string, std::unique_ptr<sf::Sound>> _sounds;
		std::map<std::string, std::unique_ptr<sf::Music>> _musics;
		typedef struct {
			audioType audio;
			audioActionType action;
			std::string index;
		} MusicEvent;
		std::vector<MusicEvent> _events;
	};
}