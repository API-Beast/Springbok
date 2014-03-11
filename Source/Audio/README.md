# Audio Module

## Loading and Playing
```cpp
SoundSource explosionSfx("explosion.ogg");
```

Loads the file "explosion.ogg" via the [ResourceManager](../Resources/README.md), this means it will only load the data if it isn't in memory already.

The memory is managed by the ResourceManager, not by the SoundSource.

At the moment *.ogg* is the only supported audio format.

```cpp
explosionSfx.play(position); // Position is a Vec2
```

Now you can play the sound file at any point as many times as you want.

SoundSource also has a few parameters that influence how new instances of that sound are played.
```cpp
// This is tiny cute explosion, make it half as loud.
explosionSfx.Volume = 0.5f;

// Pitch the sound randomly. Do this each time you play the sound to make it sound less monotonous.
explosionSfx.Pitch = 1.0f + gRNG.getNumber(-0.1f, 0.1f); 

// Make the explosion still audible even 5 screens away.
explosionSfx.MinRange =  3000; // Default is 1500, at this distance the sound will be heard at full volume.
explosionSfx.MaxRange = 10000; // Default is 2500, at this distance the sound will be barely audible.
```

The hearing distance depends on the listener position and should be set to your camera position each frame.

```cpp
SoundManager* manager = SoundManager::GetInstance();
manager->setListenerPosition(Player.Position);
```

## Managing long playing Sounds / Music

`SoundSource.play` returns a pointer to a `SoundInstance`, this object reflects the current status of the played sound.

```cpp
SoundSource MainTheme("Music/FuckYeah42.ogg");
SoundInstance* Music;
Music = MainTheme.playGlobal();
// Prevent the SoundManager from accidentally deleting the SoundInstance
Music->Permanent = true;
// [...]
// Execute this every frame to play the music on repeat
if(music->isFinished())
{
  music->setOffset(0); // Rewind.
  music->resume();     // And play!
};
```

Sound instances played by `SoundSource.play` are managed by the `SoundManager`. As such their memory doesn't need to be freed manually.

Just make sure you reset the Permanent property as soon as you don't need the sound instance anymore.
```cpp
// The music isn't needed anymore
Music->Permanent = false;
Music = nullptr;
```

The volume and pitch can also be modified during runtime:
```cpp
if(Player->Underwater)
{
  Music->setVolume(0.75f); // Underwater you don't hear as well
  Music->setPitch(0.5f);   // Underwater time just runs half as fast.
}
else
{
  Music->setVolume(1.0f);
  Music->setPitch(1.0f);
}
```

## Global volume control
You can discern between different types of Audio by giving the AudioSources different channels. Then you can set the volume for each channel seperated.

```cpp
explosionSfx.Channel = 0;
MainTheme.Channel = 1;
[... load Config ...]
SoundManager* manager = SoundManager::GetInstance();
manager->setChannelVolume(0, Config.SoundVolume * Config.GlobalVolume);
manager->setChannelVolume(1, Config.MusicVolume * Config.GlobalVolume);
```

Note that the number of Channels is hard-coded to 16.