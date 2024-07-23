/*
 * Copyright 2014-2015 Daniel Collin. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bgfx/bgfx.h>
#include <bgfx/embedded_shader.h>
#include <bx/allocator.h>
#include <bx/math.h>
#include <bx/timer.h>
#include <dear-imgui/imgui.h>
#include <dear-imgui/imgui_internal.h>

#include "imgui.h"
#include "../bgfx_utils.h"

#ifndef USE_ENTRY
#	if defined(SCI_NAMESPACE)
#		define USE_ENTRY 1
#	else
#		define USE_ENTRY 0
#	endif // defined(SCI_NAMESPACE)
#endif // USE_ENTRY

#if USE_ENTRY
#	include "../entry/entry.h"
#	include "../entry/input.h"
#endif // USE_ENTRY

#if defined(SCI_NAMESPACE)
#	include "scintilla.h"
#endif // defined(SCI_NAMESPACE)

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"
#include "vs_imgui_image.bin.h"
#include "fs_imgui_image.bin.h"

#include "roboto_regular.ttf.h"
#include "robotomono_regular.ttf.h"
#include "icons_kenney.ttf.h"
#include "icons_font_awesome.ttf.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] =
{
	BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(vs_imgui_image),
	BGFX_EMBEDDED_SHADER(fs_imgui_image),

	BGFX_EMBEDDED_SHADER_END()
};

struct FontRangeMerge
{
	const void* data;
	size_t      size;
	ImWchar     ranges[3];
};

static FontRangeMerge s_fontRangeMerge[] =
{
	{ s_iconsKenneyTtf,      sizeof(s_iconsKenneyTtf),      { ICON_MIN_KI, ICON_MAX_KI, 0 } },
	{ s_iconsFontAwesomeTtf, sizeof(s_iconsFontAwesomeTtf), { ICON_MIN_FA, ICON_MAX_FA, 0 } },
};

static void* memAlloc(size_t _size, void* _userData);
static void memFree(void* _ptr, void* _userData);

void OcornutImguiContext::render(ImDrawData* _drawData)
{
<<<<<<< HEAD
    const ImGuiIO& io = ImGui::GetIO();
    const float width  = io.DisplaySize.x * io.DisplayFramebufferScale.x;
    const float height = io.DisplaySize.y * io.DisplayFramebufferScale.y;
=======
	void render(ImDrawData* _drawData)
	{
		// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
		int32_t dispWidth  = _drawData->DisplaySize.x * _drawData->FramebufferScale.x;
		int32_t dispHeight = _drawData->DisplaySize.y * _drawData->FramebufferScale.y;
		if (dispWidth  <= 0
		||  dispHeight <= 0)
		{
			return;
		}
>>>>>>> upstream/master

    bgfx::setViewName(m_viewId, "ImGui");
    bgfx::setViewMode(m_viewId, bgfx::ViewMode::Sequential);

<<<<<<< HEAD
    const bgfx::Caps* caps = bgfx::getCaps();
    {
        float L = _drawData->DisplayPos.x;
        float R = _drawData->DisplayPos.x + _drawData->DisplaySize.x;
        float T = _drawData->DisplayPos.y;
        float B = _drawData->DisplayPos.y + _drawData->DisplaySize.y;
        float ortho[16];
        bx::mtxOrtho(ortho, L, R, B, T, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
        bgfx::setViewTransform(m_viewId, NULL, ortho);
        bgfx::setViewRect(m_viewId, 0, 0, uint16_t(width), uint16_t(height));
    }

    // Render command lists
    for (int32_t ii = 0, num = _drawData->CmdListsCount; ii < num; ++ii)
    {
        bgfx::TransientVertexBuffer tvb;
        bgfx::TransientIndexBuffer tib;
=======
		const bgfx::Caps* caps = bgfx::getCaps();
		{
			float ortho[16];
			float x = _drawData->DisplayPos.x;
			float y = _drawData->DisplayPos.y;
			float width = _drawData->DisplaySize.x;
			float height = _drawData->DisplaySize.y;

			bx::mtxOrtho(ortho, x, x + width, y + height, y, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
			bgfx::setViewTransform(m_viewId, NULL, ortho);
			bgfx::setViewRect(m_viewId, 0, 0, uint16_t(width), uint16_t(height) );
		}

		const ImVec2 clipPos   = _drawData->DisplayPos;       // (0,0) unless using multi-viewports
		const ImVec2 clipScale = _drawData->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

		// Render command lists
		for (int32_t ii = 0, num = _drawData->CmdListsCount; ii < num; ++ii)
		{
			bgfx::TransientVertexBuffer tvb;
			bgfx::TransientIndexBuffer tib;
>>>>>>> upstream/master

        const ImDrawList* drawList = _drawData->CmdLists[ii];
        uint32_t numVertices = (uint32_t)drawList->VtxBuffer.size();
        uint32_t numIndices  = (uint32_t)drawList->IdxBuffer.size();

        if (!checkAvailTransientBuffers(numVertices, m_decl, numIndices) )
        {
            // not enough space in transient buffer just quit drawing the rest...
            break;
        }

<<<<<<< HEAD
        bgfx::allocTransientVertexBuffer(&tvb, numVertices, m_decl);
        bgfx::allocTransientIndexBuffer(&tib, numIndices);
=======
			bgfx::allocTransientVertexBuffer(&tvb, numVertices, m_layout);
			bgfx::allocTransientIndexBuffer(&tib, numIndices, sizeof(ImDrawIdx) == 4);
>>>>>>> upstream/master

        ImDrawVert* verts = (ImDrawVert*)tvb.data;
        bx::memCopy(verts, drawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert) );

        ImDrawIdx* indices = (ImDrawIdx*)tib.data;
        bx::memCopy(indices, drawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx) );

<<<<<<< HEAD
        uint32_t offset = 0;
        for (const ImDrawCmd* cmd = drawList->CmdBuffer.begin(), *cmdEnd = drawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd)
        {
            if (cmd->UserCallback)
            {
                cmd->UserCallback(drawList, cmd);
            }
            else if (0 != cmd->ElemCount)
            {
                uint64_t state = 0
                    | BGFX_STATE_WRITE_RGB
                    | BGFX_STATE_WRITE_A
                    | BGFX_STATE_MSAA
                    ;
=======
			bgfx::Encoder* encoder = bgfx::begin();

			for (const ImDrawCmd* cmd = drawList->CmdBuffer.begin(), *cmdEnd = drawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd)
			{
				if (cmd->UserCallback)
				{
					cmd->UserCallback(drawList, cmd);
				}
				else if (0 != cmd->ElemCount)
				{
					uint64_t state = 0
						| BGFX_STATE_WRITE_RGB
						| BGFX_STATE_WRITE_A
						| BGFX_STATE_MSAA
						;
>>>>>>> upstream/master

                bgfx::TextureHandle th = m_texture;
                bgfx::ProgramHandle program = m_program;

<<<<<<< HEAD
                if (NULL != cmd->TextureId)
                {
                    union { ImTextureID ptr; struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; } texture = { cmd->TextureId };
                    state |= 0 != (IMGUI_FLAGS_ALPHA_BLEND & texture.s.flags)
                        ? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
                        : BGFX_STATE_NONE
                        ;
                    th = texture.s.handle;
                    if (0 != texture.s.mip)
                    {
                        const float lodEnabled[4] = { float(texture.s.mip), 1.0f, 0.0f, 0.0f };
                        bgfx::setUniform(u_imageLodEnabled, lodEnabled);
                        program = m_imageProgram;
                    }
                }
                else
                {
                    state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
                }

                const uint16_t xx = uint16_t(bx::max(cmd->ClipRect.x * io.DisplayFramebufferScale.x, 0.0f) );
                const uint16_t yy = uint16_t(bx::max(cmd->ClipRect.y * io.DisplayFramebufferScale.y, 0.0f) );
                bgfx::setScissor(xx, yy
                        , uint16_t(bx::min(cmd->ClipRect.z * io.DisplayFramebufferScale.x, 65535.0f)-xx)
                        , uint16_t(bx::min(cmd->ClipRect.w * io.DisplayFramebufferScale.y, 65535.0f)-yy)
                        );

                bgfx::setState(state);
                bgfx::setTexture(0, s_tex, th);
                bgfx::setVertexBuffer(0, &tvb, 0, numVertices);
                bgfx::setIndexBuffer(&tib, offset, cmd->ElemCount);
                bgfx::submit(m_viewId, program);
            }

            offset += cmd->ElemCount;
        }
    }
}

void OcornutImguiContext::create(float _fontSize, bx::AllocatorI* _allocator)
{
    m_allocator = _allocator;
=======
					if (NULL != cmd->TextureId)
					{
						union { ImTextureID ptr; struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; } texture = { cmd->TextureId };

						state |= 0 != (IMGUI_FLAGS_ALPHA_BLEND & texture.s.flags)
							? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
							: BGFX_STATE_NONE
							;
						th = texture.s.handle;

						if (0 != texture.s.mip)
						{
							const float lodEnabled[4] = { float(texture.s.mip), 1.0f, 0.0f, 0.0f };
							bgfx::setUniform(u_imageLodEnabled, lodEnabled);
							program = m_imageProgram;
						}
					}
					else
					{
						state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
					}

					// Project scissor/clipping rectangles into framebuffer space
					ImVec4 clipRect;
					clipRect.x = (cmd->ClipRect.x - clipPos.x) * clipScale.x;
					clipRect.y = (cmd->ClipRect.y - clipPos.y) * clipScale.y;
					clipRect.z = (cmd->ClipRect.z - clipPos.x) * clipScale.x;
					clipRect.w = (cmd->ClipRect.w - clipPos.y) * clipScale.y;

					if (clipRect.x <  dispWidth
					&&  clipRect.y <  dispHeight
					&&  clipRect.z >= 0.0f
					&&  clipRect.w >= 0.0f)
					{
						const uint16_t xx = uint16_t(bx::max(clipRect.x, 0.0f) );
						const uint16_t yy = uint16_t(bx::max(clipRect.y, 0.0f) );
						encoder->setScissor(xx, yy
								, uint16_t(bx::min(clipRect.z, 65535.0f)-xx)
								, uint16_t(bx::min(clipRect.w, 65535.0f)-yy)
								);

						encoder->setState(state);
						encoder->setTexture(0, s_tex, th);
						encoder->setVertexBuffer(0, &tvb, cmd->VtxOffset, numVertices);
						encoder->setIndexBuffer(&tib, cmd->IdxOffset, cmd->ElemCount);
						encoder->submit(m_viewId, program);
					}
				}
			}

			bgfx::end(encoder);
		}
	}

	void create(float _fontSize, bx::AllocatorI* _allocator)
	{
		IMGUI_CHECKVERSION();

		m_allocator = _allocator;
>>>>>>> upstream/master

    if (NULL == _allocator)
    {
        static bx::DefaultAllocator allocator;
        m_allocator = &allocator;
    }

    m_viewId = 255;
    m_lastScroll = 0;
    m_last = bx::getHPCounter();

    ImGui::SetAllocatorFunctions(memAlloc, memFree, NULL);

    m_imgui = ImGui::CreateContext();
    ImGui::SetCurrentContext(m_imgui);
    m_imguizmo = ImGuizmo::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.DisplaySize = ImVec2(1280.0f, 720.0f);
    io.DeltaTime   = 1.0f / 60.0f;
    io.IniFilename = NULL;

    setupStyle(true);

		io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

#if USE_ENTRY
<<<<<<< HEAD
    io.KeyMap[ImGuiKey_Tab]        = (int)entry::Key::Tab;
    io.KeyMap[ImGuiKey_LeftArrow]  = (int)entry::Key::Left;
    io.KeyMap[ImGuiKey_RightArrow] = (int)entry::Key::Right;
    io.KeyMap[ImGuiKey_UpArrow]    = (int)entry::Key::Up;
    io.KeyMap[ImGuiKey_DownArrow]  = (int)entry::Key::Down;
    io.KeyMap[ImGuiKey_PageUp]     = (int)entry::Key::PageUp;
    io.KeyMap[ImGuiKey_PageDown]   = (int)entry::Key::PageDown;
    io.KeyMap[ImGuiKey_Home]       = (int)entry::Key::Home;
    io.KeyMap[ImGuiKey_End]        = (int)entry::Key::End;
    io.KeyMap[ImGuiKey_Insert]     = (int)entry::Key::Insert;
    io.KeyMap[ImGuiKey_Delete]     = (int)entry::Key::Delete;
    io.KeyMap[ImGuiKey_Backspace]  = (int)entry::Key::Backspace;
    io.KeyMap[ImGuiKey_Space]      = (int)entry::Key::Space;
    io.KeyMap[ImGuiKey_Enter]      = (int)entry::Key::Return;
    io.KeyMap[ImGuiKey_Escape]     = (int)entry::Key::Esc;
    io.KeyMap[ImGuiKey_A]          = (int)entry::Key::KeyA;
    io.KeyMap[ImGuiKey_C]          = (int)entry::Key::KeyC;
    io.KeyMap[ImGuiKey_V]          = (int)entry::Key::KeyV;
    io.KeyMap[ImGuiKey_X]          = (int)entry::Key::KeyX;
    io.KeyMap[ImGuiKey_Y]          = (int)entry::Key::KeyY;
    io.KeyMap[ImGuiKey_Z]          = (int)entry::Key::KeyZ;
=======
		for (int32_t ii = 0; ii < (int32_t)entry::Key::Count; ++ii)
		{
			m_keyMap[ii] = ImGuiKey_None;
		}

		m_keyMap[entry::Key::Esc]          = ImGuiKey_Escape;
		m_keyMap[entry::Key::Return]       = ImGuiKey_Enter;
		m_keyMap[entry::Key::Tab]          = ImGuiKey_Tab;
		m_keyMap[entry::Key::Space]        = ImGuiKey_Space;
		m_keyMap[entry::Key::Backspace]    = ImGuiKey_Backspace;
		m_keyMap[entry::Key::Up]           = ImGuiKey_UpArrow;
		m_keyMap[entry::Key::Down]         = ImGuiKey_DownArrow;
		m_keyMap[entry::Key::Left]         = ImGuiKey_LeftArrow;
		m_keyMap[entry::Key::Right]        = ImGuiKey_RightArrow;
		m_keyMap[entry::Key::Insert]       = ImGuiKey_Insert;
		m_keyMap[entry::Key::Delete]       = ImGuiKey_Delete;
		m_keyMap[entry::Key::Home]         = ImGuiKey_Home;
		m_keyMap[entry::Key::End]          = ImGuiKey_End;
		m_keyMap[entry::Key::PageUp]       = ImGuiKey_PageUp;
		m_keyMap[entry::Key::PageDown]     = ImGuiKey_PageDown;
		m_keyMap[entry::Key::Print]        = ImGuiKey_PrintScreen;
		m_keyMap[entry::Key::Plus]         = ImGuiKey_Equal;
		m_keyMap[entry::Key::Minus]        = ImGuiKey_Minus;
		m_keyMap[entry::Key::LeftBracket]  = ImGuiKey_LeftBracket;
		m_keyMap[entry::Key::RightBracket] = ImGuiKey_RightBracket;
		m_keyMap[entry::Key::Semicolon]    = ImGuiKey_Semicolon;
		m_keyMap[entry::Key::Quote]        = ImGuiKey_Apostrophe;
		m_keyMap[entry::Key::Comma]        = ImGuiKey_Comma;
		m_keyMap[entry::Key::Period]       = ImGuiKey_Period;
		m_keyMap[entry::Key::Slash]        = ImGuiKey_Slash;
		m_keyMap[entry::Key::Backslash]    = ImGuiKey_Backslash;
		m_keyMap[entry::Key::Tilde]        = ImGuiKey_GraveAccent;
		m_keyMap[entry::Key::F1]           = ImGuiKey_F1;
		m_keyMap[entry::Key::F2]           = ImGuiKey_F2;
		m_keyMap[entry::Key::F3]           = ImGuiKey_F3;
		m_keyMap[entry::Key::F4]           = ImGuiKey_F4;
		m_keyMap[entry::Key::F5]           = ImGuiKey_F5;
		m_keyMap[entry::Key::F6]           = ImGuiKey_F6;
		m_keyMap[entry::Key::F7]           = ImGuiKey_F7;
		m_keyMap[entry::Key::F8]           = ImGuiKey_F8;
		m_keyMap[entry::Key::F9]           = ImGuiKey_F9;
		m_keyMap[entry::Key::F10]          = ImGuiKey_F10;
		m_keyMap[entry::Key::F11]          = ImGuiKey_F11;
		m_keyMap[entry::Key::F12]          = ImGuiKey_F12;
		m_keyMap[entry::Key::NumPad0]      = ImGuiKey_Keypad0;
		m_keyMap[entry::Key::NumPad1]      = ImGuiKey_Keypad1;
		m_keyMap[entry::Key::NumPad2]      = ImGuiKey_Keypad2;
		m_keyMap[entry::Key::NumPad3]      = ImGuiKey_Keypad3;
		m_keyMap[entry::Key::NumPad4]      = ImGuiKey_Keypad4;
		m_keyMap[entry::Key::NumPad5]      = ImGuiKey_Keypad5;
		m_keyMap[entry::Key::NumPad6]      = ImGuiKey_Keypad6;
		m_keyMap[entry::Key::NumPad7]      = ImGuiKey_Keypad7;
		m_keyMap[entry::Key::NumPad8]      = ImGuiKey_Keypad8;
		m_keyMap[entry::Key::NumPad9]      = ImGuiKey_Keypad9;
		m_keyMap[entry::Key::Key0]         = ImGuiKey_0;
		m_keyMap[entry::Key::Key1]         = ImGuiKey_1;
		m_keyMap[entry::Key::Key2]         = ImGuiKey_2;
		m_keyMap[entry::Key::Key3]         = ImGuiKey_3;
		m_keyMap[entry::Key::Key4]         = ImGuiKey_4;
		m_keyMap[entry::Key::Key5]         = ImGuiKey_5;
		m_keyMap[entry::Key::Key6]         = ImGuiKey_6;
		m_keyMap[entry::Key::Key7]         = ImGuiKey_7;
		m_keyMap[entry::Key::Key8]         = ImGuiKey_8;
		m_keyMap[entry::Key::Key9]         = ImGuiKey_9;
		m_keyMap[entry::Key::KeyA]         = ImGuiKey_A;
		m_keyMap[entry::Key::KeyB]         = ImGuiKey_B;
		m_keyMap[entry::Key::KeyC]         = ImGuiKey_C;
		m_keyMap[entry::Key::KeyD]         = ImGuiKey_D;
		m_keyMap[entry::Key::KeyE]         = ImGuiKey_E;
		m_keyMap[entry::Key::KeyF]         = ImGuiKey_F;
		m_keyMap[entry::Key::KeyG]         = ImGuiKey_G;
		m_keyMap[entry::Key::KeyH]         = ImGuiKey_H;
		m_keyMap[entry::Key::KeyI]         = ImGuiKey_I;
		m_keyMap[entry::Key::KeyJ]         = ImGuiKey_J;
		m_keyMap[entry::Key::KeyK]         = ImGuiKey_K;
		m_keyMap[entry::Key::KeyL]         = ImGuiKey_L;
		m_keyMap[entry::Key::KeyM]         = ImGuiKey_M;
		m_keyMap[entry::Key::KeyN]         = ImGuiKey_N;
		m_keyMap[entry::Key::KeyO]         = ImGuiKey_O;
		m_keyMap[entry::Key::KeyP]         = ImGuiKey_P;
		m_keyMap[entry::Key::KeyQ]         = ImGuiKey_Q;
		m_keyMap[entry::Key::KeyR]         = ImGuiKey_R;
		m_keyMap[entry::Key::KeyS]         = ImGuiKey_S;
		m_keyMap[entry::Key::KeyT]         = ImGuiKey_T;
		m_keyMap[entry::Key::KeyU]         = ImGuiKey_U;
		m_keyMap[entry::Key::KeyV]         = ImGuiKey_V;
		m_keyMap[entry::Key::KeyW]         = ImGuiKey_W;
		m_keyMap[entry::Key::KeyX]         = ImGuiKey_X;
		m_keyMap[entry::Key::KeyY]         = ImGuiKey_Y;
		m_keyMap[entry::Key::KeyZ]         = ImGuiKey_Z;
>>>>>>> upstream/master

    io.ConfigFlags |= 0
        | ImGuiConfigFlags_NavEnableGamepad
        | ImGuiConfigFlags_NavEnableKeyboard
        ;

<<<<<<< HEAD
    io.NavInputs[ImGuiNavInput_Activate]    = (int)entry::Key::GamepadA;
    io.NavInputs[ImGuiNavInput_Cancel]      = (int)entry::Key::GamepadB;
//        io.NavInputs[ImGuiNavInput_Input]       = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_Menu]        = (int)entry::Key::;
    io.NavInputs[ImGuiNavInput_DpadLeft]    = (int)entry::Key::GamepadLeft;
    io.NavInputs[ImGuiNavInput_DpadRight]   = (int)entry::Key::GamepadRight;
    io.NavInputs[ImGuiNavInput_DpadUp]      = (int)entry::Key::GamepadUp;
    io.NavInputs[ImGuiNavInput_DpadDown]    = (int)entry::Key::GamepadDown;
//        io.NavInputs[ImGuiNavInput_LStickLeft]  = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_LStickRight] = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_LStickUp]    = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_LStickDown]  = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_FocusPrev]   = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_FocusNext]   = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_TweakSlow]   = (int)entry::Key::;
//        io.NavInputs[ImGuiNavInput_TweakFast]   = (int)entry::Key::;
=======
		m_keyMap[entry::Key::GamepadStart]     = ImGuiKey_GamepadStart;
		m_keyMap[entry::Key::GamepadBack]      = ImGuiKey_GamepadBack;
		m_keyMap[entry::Key::GamepadY]         = ImGuiKey_GamepadFaceUp;
		m_keyMap[entry::Key::GamepadA]         = ImGuiKey_GamepadFaceDown;
		m_keyMap[entry::Key::GamepadX]         = ImGuiKey_GamepadFaceLeft;
		m_keyMap[entry::Key::GamepadB]         = ImGuiKey_GamepadFaceRight;
		m_keyMap[entry::Key::GamepadUp]        = ImGuiKey_GamepadDpadUp;
		m_keyMap[entry::Key::GamepadDown]      = ImGuiKey_GamepadDpadDown;
		m_keyMap[entry::Key::GamepadLeft]      = ImGuiKey_GamepadDpadLeft;
		m_keyMap[entry::Key::GamepadRight]     = ImGuiKey_GamepadDpadRight;
		m_keyMap[entry::Key::GamepadShoulderL] = ImGuiKey_GamepadL1;
		m_keyMap[entry::Key::GamepadShoulderR] = ImGuiKey_GamepadR1;
		m_keyMap[entry::Key::GamepadThumbL]    = ImGuiKey_GamepadL3;
		m_keyMap[entry::Key::GamepadThumbR]    = ImGuiKey_GamepadR3;
>>>>>>> upstream/master
#endif // USE_ENTRY

    bgfx::RendererType::Enum type = bgfx::getRendererType();
    m_program = bgfx::createProgram(
          bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_ocornut_imgui")
        , bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_ocornut_imgui")
        , true
        );

    u_imageLodEnabled = bgfx::createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);
    m_imageProgram = bgfx::createProgram(
          bgfx::createEmbeddedShader(s_embeddedShaders, type, "vs_imgui_image")
        , bgfx::createEmbeddedShader(s_embeddedShaders, type, "fs_imgui_image")
        , true
        );

    m_decl
        .begin()
        .add(bgfx::Attrib::Position,  2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0,    4, bgfx::AttribType::Uint8, true)
        .end();

    s_tex = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

    uint8_t* data;
    int32_t width;
    int32_t height;
    {
        ImFontConfig config;
        config.FontDataOwnedByAtlas = false;
        config.MergeMode = false;
//            config.MergeGlyphCenterV = true;

        const ImWchar* ranges = io.Fonts->GetGlyphRangesCyrillic();
        m_font[ImGui::Font::Regular] = io.Fonts->AddFontFromMemoryTTF( (void*)s_robotoRegularTtf,     sizeof(s_robotoRegularTtf),     _fontSize,      &config, ranges);
        m_font[ImGui::Font::Mono   ] = io.Fonts->AddFontFromMemoryTTF( (void*)s_robotoMonoRegularTtf, sizeof(s_robotoMonoRegularTtf), _fontSize-3.0f, &config, ranges);

        config.MergeMode = true;
        config.DstFont   = m_font[ImGui::Font::Regular];

        for (uint32_t ii = 0; ii < BX_COUNTOF(s_fontRangeMerge); ++ii)
        {
            const FontRangeMerge& frm = s_fontRangeMerge[ii];

            io.Fonts->AddFontFromMemoryTTF( (void*)frm.data
                    , (int)frm.size
                    , _fontSize-3.0f
                    , &config
                    , frm.ranges
                    );
        }
    }

    io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);

    m_texture = bgfx::createTexture2D(
          (uint16_t)width
        , (uint16_t)height
        , false
        , 1
        , bgfx::TextureFormat::BGRA8
        , 0
        , bgfx::copy(data, width*height*4)
        );
}

void OcornutImguiContext::destroy()
{
    ImGui::SetCurrentContext(m_imgui);
    ImGui::DestroyContext(m_imgui);
    ImGuizmo::DestroyContext(m_imguizmo);
    
    bgfx::destroy(s_tex);
    bgfx::destroy(m_texture);

    bgfx::destroy(u_imageLodEnabled);
    bgfx::destroy(m_imageProgram);
    bgfx::destroy(m_program);

    m_allocator = NULL;
}

void OcornutImguiContext::setupStyle(bool _dark)
{
    // Doug Binks' darl color scheme
    // https://gist.github.com/dougbinks/8089b4bbaccaaf6fa204236978d165a9
    ImGuiStyle& style = ImGui::GetStyle();
    if (_dark)
    {
        ImGui::StyleColorsDark(&style);
    }
    else
    {
        ImGui::StyleColorsLight(&style);
    }

    style.FrameRounding    = 4.0f;
    style.WindowBorderSize = 0.0f;
}

void OcornutImguiContext::beginFrame(
      int32_t _mx
    , int32_t _my
    , uint8_t _button
    , int32_t _scroll
    , int _width
    , int _height
    , char _inputChar
    , bgfx::ViewId _viewId
    )
{
    ImGui::SetCurrentContext(m_imgui);
    m_viewId = _viewId;

    ImGuiIO& io = ImGui::GetIO();
//    if (_inputChar < 0x7f)
//    {
//        io.AddInputCharacter(_inputChar); // ASCII or GTFO! :(
//    }

    io.DisplaySize = ImVec2( (float)_width, (float)_height);

    const int64_t now = bx::getHPCounter();
    const int64_t frameTime = now - m_last;
    m_last = now;
    const double freq = double(bx::getHPFrequency() );
    io.DeltaTime = bx::max(float(frameTime/freq), 0.001f);

<<<<<<< HEAD
    io.MousePos = ImVec2( (float)_mx, (float)_my);
    io.MouseDown[0] = 0 != (_button & IMGUI_MBUT_LEFT);
    io.MouseDown[1] = 0 != (_button & IMGUI_MBUT_RIGHT);
    io.MouseDown[2] = 0 != (_button & IMGUI_MBUT_MIDDLE);
    io.MouseWheel = (float)(_scroll - m_lastScroll);
    m_lastScroll = _scroll;

#if USE_ENTRY
    uint8_t modifiers = inputGetModifiersState();
    io.KeyShift = 0 != (modifiers & (entry::Modifier::LeftShift | entry::Modifier::RightShift) );
    io.KeyCtrl  = 0 != (modifiers & (entry::Modifier::LeftCtrl  | entry::Modifier::RightCtrl ) );
    io.KeyAlt   = 0 != (modifiers & (entry::Modifier::LeftAlt   | entry::Modifier::RightAlt  ) );
    for (int32_t ii = 0; ii < (int32_t)entry::Key::Count; ++ii)
    {
        io.KeysDown[ii] = inputGetKeyState(entry::Key::Enum(ii) );
    }
=======
		io.DisplaySize = ImVec2( (float)_width, (float)_height);

		const int64_t now = bx::getHPCounter();
		const int64_t frameTime = now - m_last;
		m_last = now;
		const double freq = double(bx::getHPFrequency() );
		io.DeltaTime = float(frameTime/freq);

		io.AddMousePosEvent( (float)_mx, (float)_my);
		io.AddMouseButtonEvent(ImGuiMouseButton_Left,   0 != (_button & IMGUI_MBUT_LEFT  ) );
		io.AddMouseButtonEvent(ImGuiMouseButton_Right,  0 != (_button & IMGUI_MBUT_RIGHT ) );
		io.AddMouseButtonEvent(ImGuiMouseButton_Middle, 0 != (_button & IMGUI_MBUT_MIDDLE) );
		io.AddMouseWheelEvent(0.0f, (float)(_scroll - m_lastScroll) );
		m_lastScroll = _scroll;

#if USE_ENTRY
		uint8_t modifiers = inputGetModifiersState();
		io.AddKeyEvent(ImGuiMod_Shift, 0 != (modifiers & (entry::Modifier::LeftShift | entry::Modifier::RightShift) ) );
		io.AddKeyEvent(ImGuiMod_Ctrl,  0 != (modifiers & (entry::Modifier::LeftCtrl  | entry::Modifier::RightCtrl ) ) );
		io.AddKeyEvent(ImGuiMod_Alt,   0 != (modifiers & (entry::Modifier::LeftAlt   | entry::Modifier::RightAlt  ) ) );
		io.AddKeyEvent(ImGuiMod_Super, 0 != (modifiers & (entry::Modifier::LeftMeta  | entry::Modifier::RightMeta ) ) );
		for (int32_t ii = 0; ii < (int32_t)entry::Key::Count; ++ii)
		{
			io.AddKeyEvent(m_keyMap[ii], inputGetKeyState(entry::Key::Enum(ii) ) );
			io.SetKeyEventNativeData(m_keyMap[ii], 0, 0, ii);
		}
>>>>>>> upstream/master
#endif // USE_ENTRY

    ImGui::NewFrame();

    ImGuizmo::SetCurrentContext(m_imguizmo);
    ImGuizmo::BeginFrame();
}

void OcornutImguiContext::endFrame()
{
    ImGui::SetCurrentContext(m_imgui);
    ImGui::Render();
    render(ImGui::GetDrawData() );
}

<<<<<<< HEAD
ImGuiIO& OcornutImguiContext::io()
{
    ImGui::SetCurrentContext(m_imgui);
    return ImGui::GetIO();
}
=======
	ImGuiContext*       m_imgui;
	bx::AllocatorI*     m_allocator;
	bgfx::VertexLayout  m_layout;
	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_imageProgram;
	bgfx::TextureHandle m_texture;
	bgfx::UniformHandle s_tex;
	bgfx::UniformHandle u_imageLodEnabled;
	ImFont* m_font[ImGui::Font::Count];
	int64_t m_last;
	int32_t m_lastScroll;
	bgfx::ViewId m_viewId;
#if USE_ENTRY
	ImGuiKey m_keyMap[(int)entry::Key::Count];
#endif // USE_ENTRY
};
>>>>>>> upstream/master

static OcornutImguiContext s_ctx;

static bx::DefaultAllocator s_allocator;

static void* memAlloc(size_t _size, void* _userData)
{
	BX_UNUSED(_userData);
<<<<<<< HEAD
	return BX_ALLOC(&s_allocator, _size);
=======
	return bx::alloc(s_ctx.m_allocator, _size);
>>>>>>> upstream/master
}

static void memFree(void* _ptr, void* _userData)
{
	BX_UNUSED(_userData);
<<<<<<< HEAD
	BX_FREE(&s_allocator, _ptr);
=======
	bx::free(s_ctx.m_allocator, _ptr);
>>>>>>> upstream/master
}

void imguiCreate(float _fontSize, bx::AllocatorI* _allocator)
{
	s_ctx.create(_fontSize, _allocator);
}

void imguiDestroy()
{
	s_ctx.destroy();
}

void imguiBeginFrame(int32_t _mx, int32_t _my, uint8_t _button, int32_t _scroll, uint16_t _width, uint16_t _height, char _inputChar, bgfx::ViewId _viewId)
{
	s_ctx.beginFrame(_mx, _my, _button, _scroll, _width, _height, _inputChar, _viewId);
}

void imguiEndFrame()
{
	s_ctx.endFrame();
}

namespace ImGui
{
	void PushFont(Font::Enum _font)
	{
		PushFont(s_ctx.m_font[_font]);
	}

	void PushEnabled(bool _enabled)
	{
		extern void PushItemFlag(int option, bool enabled);
		PushItemFlag(ImGuiItemFlags_Disabled, !_enabled);
		PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * (_enabled ? 1.0f : 0.5f) );
	}

	void PopEnabled()
	{
		extern void PopItemFlag();
		PopItemFlag();
		PopStyleVar();
	}

} // namespace ImGui

BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4505); // error C4505: '' : unreferenced local function has been removed
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-function"); // warning: ‘int rect_width_compare(const void*, const void*)’ defined but not used
BX_PRAGMA_DIAGNOSTIC_PUSH();
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG("-Wunknown-pragmas")
//BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wunused-but-set-variable"); // warning: variable ‘L1’ set but not used
BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wtype-limits"); // warning: comparison is always true due to limited range of data type

#define STBTT_ifloor(_a)   int32_t(bx::floor(_a) )
#define STBTT_iceil(_a)    int32_t(bx::ceil(_a) )
#define STBTT_sqrt(_a)     bx::sqrt(_a)
#define STBTT_pow(_a, _b)  bx::pow(_a, _b)
#define STBTT_fmod(_a, _b) bx::mod(_a, _b)
#define STBTT_cos(_a)      bx::cos(_a)
#define STBTT_acos(_a)     bx::acos(_a)
#define STBTT_fabs(_a)     bx::abs(_a)
#define STBTT_strlen(_str) bx::strLen(_str)

#define STBTT_memcpy(_dst, _src, _numBytes) bx::memCopy(_dst, _src, _numBytes)
#define STBTT_memset(_dst, _ch, _numBytes)  bx::memSet(_dst, _ch, _numBytes)
#define STBTT_malloc(_size, _userData)      memAlloc(_size, _userData)
#define STBTT_free(_ptr, _userData)         memFree(_ptr, _userData)

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb/stb_rect_pack.h>
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>
BX_PRAGMA_DIAGNOSTIC_POP();
