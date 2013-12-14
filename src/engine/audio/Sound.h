/*
===========================================================================

daemon gpl source code
copyright (c) 2013 unvanquished developers

this file is part of the daemon gpl source code (daemon source code).

daemon source code is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

daemon source code is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with daemon source code.  if not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

#include "snd_local.h"
#include "snd_codec.h"

#ifndef AUDIO_SOUND_H_
#define AUDIO_SOUND_H_

namespace Audio {

    class Emitter;
    class Sound;

    void InitSounds();
    void ShutdownSounds();
    void UpdateSounds();

    void AddSound(Emitter* emitter, Sound* sound, int priority);

    struct sourceRecord_t;
    class Sample;

    namespace AL {
        class Source;
    }

    //TODO sound.mute
    class Sound {
        public:
            Sound();
            virtual ~Sound();

            void Play();

            void AcquireSource(sourceRecord_t* source);
            AL::Source& GetSource();
            void SetEmitter(Emitter* emitter);

            virtual void SetupSource(AL::Source& source) = 0;
            virtual void Update() = 0;

        private:
            Emitter* emitter;
            sourceRecord_t* source;
    };

    class OneShotSound : public Sound {
        public:
            OneShotSound(Sample* sample);
            virtual ~OneShotSound();

            virtual void SetupSource(AL::Source& source) OVERRIDE;
            virtual void Update() OVERRIDE;

        private:
            Sample* sample;
    };

/*
    class LoopingSound : public Sound {
        public:
            LoopingSound(Sample* sample);
            virtual ~LoopingSound();

            virtual void SetupSource(AL::Source& source) OVERRIDE;

        private:
            Sample* sample;
    };
*/
    // StreamSound
    // MusicSound?

}

#endif //AUDIO_SOUND_H_
