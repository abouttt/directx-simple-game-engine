#pragma once

class Object
{
public:
	Object();
	virtual ~Object() = default;

public:
	virtual bool IsActive() const;
	virtual void SetActive(bool bActive);

	virtual const std::wstring& GetName() const = 0;
	virtual void SetName(const std::wstring& name) = 0;

private:
	bool mbActive;
};

