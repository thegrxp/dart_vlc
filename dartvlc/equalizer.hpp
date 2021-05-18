/*
 * dart_vlc: A media playback library for Dart & Flutter. Based on libVLC & libVLC++.
 * 
 * Hitesh Kumar Saini, Domingo Montesdeoca Gonzalez & contributors.
 * https://github.com/alexmercerind
 * alexmercerind@gmail.com
 * 
 * GNU Lesser General Public License v2.1
 */

#include <map>

#include "vlcpp/vlc.hpp"

#ifndef Equalizer_HEADER
#define Equalizer_HEADER


enum EqualizerMode {
	flat,
	classical,
	club,
	dance,
	fullBass,
	fullBassAndTreble,
	fullTreble,
	headphones,
	largeHall,
	live,
	party,
	pop,
	reggae,
	rock,
	ska,
	soft,
	softRock,
	techno
};



class Equalizer {
public:
	float preAmp;
	std::map<float, float> bandAmps;

	Equalizer() {
		this->equalizer = VLC::Equalizer();
		for (uint32_t index = 0; index < this->equalizer.bandCount(); index++) this->bands[this->equalizer.bandFrequency(index)] = index;
		this->refresh();
	}

	Equalizer(EqualizerMode mode) {
		this->equalizer = VLC::Equalizer(
			static_cast<int>(mode)
		);
		for (uint32_t index = 0; index < this->equalizer.bandCount(); index++) this->bands[this->equalizer.bandFrequency(index)] = index;
		this->refresh();
	}

	void setBandAmp(float band, float amps) {
		this->equalizer.setAmp(
			amps,
			bands[band]
		);
		this->refresh();
	}

	void setPreAmp(float amp) {
		this->equalizer.setPreamp(amp);
		this->refresh();
	}

private:
	VLC::Equalizer equalizer;
	std::map<float, int> bands;

	void refresh() {
		for (uint32_t index = 0; index < this->equalizer.bandCount(); index++) this->bandAmps[this->equalizer.bandFrequency(index)] = this->equalizer.amp(index);
		this->preAmp = this->equalizer.preamp();
	}

	friend class PlayerSetters;
};


class Equalizers {
public:
	Equalizer* get(int id) {
		return this->equalizers[id];
	}

	int createEmpty() {
		this->equalizers[static_cast<int>(this->equalizers.size())] = new Equalizer();
		return static_cast<int>(this->equalizers.size());
	}

	int createMode(EqualizerMode mode) {
		this->equalizers[static_cast<int>(this->equalizers.size())] = new Equalizer(mode);
		return static_cast<int>(this->equalizers.size());
	}

private:
	std::map<int, Equalizer*> equalizers;
};


Equalizers* equalizers = new Equalizers();


#endif
