#pragma once
class BaseWaveException {
public:
	virtual const char* what() const noexcept = 0;
	virtual ~BaseWaveException() = default;
};