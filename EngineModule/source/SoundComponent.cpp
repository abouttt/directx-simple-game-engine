#include "pch.h"
#include "EngineUtil.h"
#include "SoundComponent.h"

FMOD::System* SoundComponent::mSystem = nullptr;

SoundComponent::SoundComponent()
	: mSound(nullptr)
	, mChannel(nullptr)
	, mPriority(128)
	, mVolume(1.f)
	, mPitch(1.f)
	, mStereoPan(0.f)
	, mbMute(false)
	, mbLoop(false)
{
}

SoundComponent::~SoundComponent()
{
	if (mSound)
	{
		mSound->release();
	}
}

bool SoundComponent::LoadSoundFile(const std::wstring& fileName)
{
	mSound->release();
	std::string finalFileName = WStringToString(_T("../Resources/Sounds/") + fileName);
	return mSystem->createSound(finalFileName.c_str(), FMOD_DEFAULT, nullptr, &mSound) == FMOD_OK;
}

void SoundComponent::Play()
{
	if (!IsActiveAndEnabled())
	{
		return;
	}

	if (mSound)
	{
		if (mChannel)
		{
			mChannel->stop();
		}

		mSystem->playSound(mSound, nullptr, true, &mChannel);
		setupChannel(false);
		mChannel->setPaused(false);
	}
}

void SoundComponent::PlayOneShot()
{
	if (!IsActiveAndEnabled())
	{
		return;
	}

	if (mSound)
	{
		mSystem->playSound(mSound, nullptr, true, &mChannel);
		setupChannel(true);
		mChannel->setPaused(false);
	}
}

void SoundComponent::Pause()
{
	if (mChannel)
	{
		mChannel->setPaused(true);
	}
}

void SoundComponent::Stop()
{
	if (mChannel)
	{
		mChannel->stop();
	}
}

void SoundComponent::UnPause()
{
	if (mChannel)
	{
		mChannel->setPaused(false);
	}
}

bool SoundComponent::IsPlaying() const
{
	if (mChannel)
	{
		bool bPlaying;
		mChannel->isPlaying(&bPlaying);
		return bPlaying;
	}

	return false;
}

bool SoundComponent::IsLoop() const
{
	return mbLoop;
}

int SoundComponent::GetPriority() const
{
	return mPriority;
}

float SoundComponent::GetVolume() const
{
	return mVolume;
}

float SoundComponent::GetPitch() const
{
	return mPitch;
}

void SoundComponent::SetPriority(const int priority)
{
	mPriority = std::clamp(priority, 0, 256);
	if (mChannel)
	{
		mChannel->setPriority(mPriority);
	}
}

void SoundComponent::SetVolume(const float volume)
{
	mVolume = std::clamp(volume, 0.f, 1.f);
	if (mChannel)
	{
		mChannel->setVolume(mVolume);
	}
}

void SoundComponent::SetPitch(const float pitch)
{
	mPitch = std::clamp(pitch, 0.f, 2.f);
	if (mChannel)
	{
		mChannel->setPitch(mPitch);
	}
}

void SoundComponent::SetStereoPan(const float stereoPan)
{
	mStereoPan = std::clamp(stereoPan, -1.f, 1.f);
	if (mChannel)
	{
		mChannel->setPan(mStereoPan);
	}
}

void SoundComponent::SetLoop(const bool bLoop)
{
	mbLoop = bLoop;
	if (mChannel)
	{
		mChannel->setMode(mbLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	}
}

void SoundComponent::SetMute(const bool bMute)
{
	mbMute = bMute;
	if (mChannel)
	{
		mChannel->setMute(mbMute);
	}
}

void SoundComponent::OnEnable()
{
	Play();
}

void SoundComponent::OnDisable()
{
	Stop();
}

void SoundComponent::setupChannel(bool bOneShot)
{
	if (!mChannel)
	{
		return;
	}

	mChannel->setPriority(mPriority);
	mChannel->setVolume(mVolume);
	mChannel->setPitch(mPitch);
	mChannel->setPan(mStereoPan);
	mChannel->setMute(mbMute);
	if (bOneShot)
	{
		mChannel->setMode(FMOD_LOOP_OFF);
	}
	else
	{
		mChannel->setMode(mbLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	}
}

bool SoundComponent::init()
{
	if (mSystem)
	{
		return false;
	}

	if (FMOD::System_Create(&mSystem) != FMOD_OK)
	{
		::MessageBox(nullptr, _T("SoundComponent/init/FMOD::System_Create : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	if (mSystem->init(32, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
	{
		::MessageBox(nullptr, _T("SoundComponent/init/FMOD::System::init : FAILED"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	return true;
}

void SoundComponent::update()
{
	mSystem->update();
}

void SoundComponent::release()
{
	if (mSystem)
	{
		mSystem->close();
		mSystem->release();
	}
}
