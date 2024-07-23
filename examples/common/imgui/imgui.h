/*
<<<<<<< HEAD
 * Copyright 2011-2019 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
=======
 * Copyright 2011-2024 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
>>>>>>> upstream/master
 */

#ifndef IMGUI_H_HEADER_GUARD
#define IMGUI_H_HEADER_GUARD

#include <bgfx/bgfx.h>
#include <dear-imgui/imgui.h>
#include <iconfontheaders/icons_kenney.h>
#include <iconfontheaders/icons_font_awesome.h>

#define IMGUI_MBUT_LEFT   0x01
#define IMGUI_MBUT_RIGHT  0x02
#define IMGUI_MBUT_MIDDLE 0x04

struct OcornutImguiContext
{
    void create(float _fontSize, bx::AllocatorI* _allocator);
    void destroy();
    void beginFrame(
          int32_t _mx
        , int32_t _my
        , uint8_t _button
        , int32_t _scroll
        , int _width
        , int _height
        , char _inputChar
        , bgfx::ViewId _viewId);
    void endFrame();
    void render(ImDrawData* _drawData);
    void setupStyle(bool _dark);
    
    ImGuiIO& io();
    
    ImGuiContext*       m_imgui;
    ImGuizmo::Context* m_imguizmo;
    bx::AllocatorI*     m_allocator;
    bgfx::VertexLayout    m_decl;
    bgfx::ProgramHandle m_program;
    bgfx::ProgramHandle m_imageProgram;
    bgfx::TextureHandle m_texture;
    bgfx::UniformHandle s_tex;
    bgfx::UniformHandle u_imageLodEnabled;
    ImFont* m_font[ImGui::Font::Count];
    int64_t m_last;
    int32_t m_lastScroll;
    bgfx::ViewId m_viewId;
};

inline uint32_t imguiRGBA(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255)
{
	return 0
		| (uint32_t(_r) <<  0)
		| (uint32_t(_g) <<  8)
		| (uint32_t(_b) << 16)
		| (uint32_t(_a) << 24)
		;
}

namespace bx { struct AllocatorI; }

void imguiCreate(float _fontSize = 18.0f, bx::AllocatorI* _allocator = NULL);
void imguiDestroy();

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar = 0, bgfx::ViewId _view = 255);
void imguiEndFrame();

namespace entry { class AppI; }
void showExampleDialog(entry::AppI* _app, const char* _errorText = NULL);

namespace ImGui
{
#define IMGUI_FLAGS_NONE        UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)

<<<<<<< HEAD
=======
	///
	inline ImTextureID toId(bgfx::TextureHandle _handle, uint8_t _flags, uint8_t _mip)
	{
		union { struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; ImTextureID id; } tex;
		tex.s.handle = _handle;
		tex.s.flags  = _flags;
		tex.s.mip    = _mip;
		return tex.id;
	}

>>>>>>> upstream/master
	// Helper function for passing bgfx::TextureHandle to ImGui::Image.
	inline void Image(bgfx::TextureHandle _handle
		, uint8_t _flags
		, uint8_t _mip
		, const ImVec2& _size
		, const ImVec2& _uv0       = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1       = ImVec2(1.0f, 1.0f)
		, const ImVec4& _tintCol   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		, const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		)
	{
		union { struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; ImTextureID ptr; } texture;
		texture.s.handle = _handle;
		texture.s.flags  = _flags;
		texture.s.mip    = _mip;
		Image(texture.ptr, _size, _uv0, _uv1, _tintCol, _borderCol);
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::Image.
	inline void Image(bgfx::TextureHandle _handle
		, const ImVec2& _size
		, const ImVec2& _uv0       = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1       = ImVec2(1.0f, 1.0f)
		, const ImVec4& _tintCol   = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		, const ImVec4& _borderCol = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		)
	{
		Image(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1, _tintCol, _borderCol);
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
	inline bool ImageButton(bgfx::TextureHandle _handle
		, uint8_t _flags
		, uint8_t _mip
		, const ImVec2& _size
		, const ImVec2& _uv0     = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1     = ImVec2(1.0f, 1.0f)
		, const ImVec4& _bgCol   = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		, const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		)
	{
<<<<<<< HEAD
		union { struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; ImTextureID ptr; } texture;
		texture.s.handle = _handle;
		texture.s.flags  = _flags;
		texture.s.mip    = _mip;
		return ImageButton(texture.ptr, _size, _uv0, _uv1, _framePadding, _bgCol, _tintCol);
=======
		return ImageButton("image", toId(_handle, _flags, _mip), _size, _uv0, _uv1, _bgCol, _tintCol);
>>>>>>> upstream/master
	}

	// Helper function for passing bgfx::TextureHandle to ImGui::ImageButton.
	inline bool ImageButton(bgfx::TextureHandle _handle
		, const ImVec2& _size
		, const ImVec2& _uv0     = ImVec2(0.0f, 0.0f)
		, const ImVec2& _uv1     = ImVec2(1.0f, 1.0f)
		, const ImVec4& _bgCol   = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)
		, const ImVec4& _tintCol = ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
		)
	{
		return ImageButton(_handle, IMGUI_FLAGS_ALPHA_BLEND, 0, _size, _uv0, _uv1, _bgCol, _tintCol);
	}

	///
	inline void NextLine()
	{
		SetCursorPosY(GetCursorPosY() + GetTextLineHeightWithSpacing() );
	}

	///
	inline bool MouseOverArea()
	{
		return false
			|| ImGui::IsAnyItemActive()
			|| ImGui::IsAnyItemHovered()
			|| ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)
//			|| ImGuizmo::IsOver()
			;
	}

	///
	void PushEnabled(bool _enabled);

	///
	void PopEnabled();

} // namespace ImGui

#endif // IMGUI_H_HEADER_GUARD
