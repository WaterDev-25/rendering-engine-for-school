#ifndef IWINDOW_HPP
#define IWINDOW_HPP

class IWindow
{
public:
	virtual ~IWindow() = default;

	virtual void Init() = 0;
};

#endif // IWINDOW_HPP
