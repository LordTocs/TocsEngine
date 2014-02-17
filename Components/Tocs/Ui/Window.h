#pragma once
#include "NativeHelpers.h"
#include "LayoutContainer.h"
#include "VectorTypes.h"
#include <functional>

namespace Tocs {
namespace Ui {

class Window : public LayoutContainer
{
protected:
	Size MinSize_;
	OSHandle Handle;
	virtual void OSAttach(LayoutAble &thing);
	virtual void OSDetach(LayoutAble &thing);
	virtual void EnforceMinimumSize(Size size);
public:
	Window(const std::string &title, Size size);
	~Window();

	Window(const Window &) = delete;

	const OSHandle &GetHandle() const { return Handle; }

	void Close();
	std::function<void()> OnClose;

	Window &Hide();
	Window &Show();

	Window &Maximize();
	std::function<void()> OnMaximize;

	Window &Minimize();
	std::function<void()> OnMinimize;

	Size MinSize() const { return MinSize_; }
	Window &MinSize(Size size);

	Window &SetPosition(unsigned int x, unsigned int y);
	Point GetPosition() const;
	std::function<void(unsigned int, unsigned int)> OnMove;

	Size GetClientSize() const;
	Size GetWindowSize() const;
	Window &SetClientSize(unsigned int w, unsigned int h);
	Window &SetClientSize(const Size &size);
	Window &SetWindowSize(unsigned int w, unsigned int h);
	Window &SetWindowSize(const Size &size);

	std::function<void(unsigned int, unsigned int)> OnResize;


	//WINDOWS ONLY
	friend LRESULT __stdcall WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

}}