/*
 * Copyright (C) 2021 Patrick Mours
 * License: https://github.com/crosire/reshade#license
 */

#pragma once

#include "reshade_api.hpp"

namespace reshade
{
	enum class addon_event
	{
		/// <summary>
		/// Called after 'IDirect3D9::CreateDevice(Ex)', 'D3D10CreateDevice(AndSwapChain)', 'D3D11CreateDevice(AndSwapChain)', 'D3D12CreateDevice', 'glMakeCurrent' or 'vkCreateDevice'.
		/// </summary>
		init_device,
		/// <summary>
		/// Called on device destruction, before 'IDirect3DDevice9::Release', 'ID3D10Device::Release', 'ID3D11Device::Release', 'ID3D12Device::Release', 'wglDeleteContext' or 'vkDestroyDevice'.
		/// </summary>
		destroy_device,
		/// <summary>
		/// Called after 'ID3D11DeviceContext::FinishCommandList', 'ID3D12Device::CreateCommandList(1)' or 'vkAllocateCommandBuffers'.
		/// </summary>
		init_command_list,
		/// <summary>
		/// Called on command list destruction, before 'ID3D11CommandList::Release', 'ID3D12CommandList::Release' or 'vkFreeCommandBuffers'.
		/// </summary>
		destroy_command_list,
		/// <summary>
		/// Called after 'ID3D12Device::CreateCommandQueue' or 'vkCreateDevice'.
		/// </summary>
		init_command_queue,
		/// <summary>
		/// Called on command queue destruction, before 'ID3D12CommandQueue::Release' or 'vkDestroyDevice'.
		/// </summary>
		destroy_command_queue,
		/// <summary>
		/// Called after effect runtime initialization (which happens after swap chain creation or a resize).
		/// </summary>
		init_effect_runtime,
		/// <summary>
		/// Called when an effect runtime is reset or destroyed.
		/// </summary>
		destroy_effect_runtime,

		/// <summary>
		/// Called before 'IDirect3Device9::Create(...)Buffer/Texture', 'IDirect3DDevice9::Create(...)Surface(Ex)', 'ID3D10Device::CreateBuffer/Texture(...)', 'ID3D11Device::CreateBuffer/Texture(...)', 'ID3D12Device::Create(...)Resource', 'gl(Named)Buffer/Tex(ture)Storage(...)' or 'vkCreateBuffer/Image'.
		/// </summary>
		create_resource,
		/// <summary>
		/// Called before 'IDirect3DDevice9::Create(...)Surface(Ex)', 'ID3D10Device::Create(...)View', 'ID3D11Device::Create(...)View', 'ID3D12Device::Create(...)View', 'glTex(ture)Buffer', 'glTextureView(...)' or 'vkCreateBuffer/ImageView'.
		/// </summary>
		create_resource_view,

		/// <summary>
		/// Called after 'IDirect3DDevice9::SetDepthStencilSurface', 'ID3D10Device::OMSetRenderTargets', 'ID3D11DeviceContext::OMSetRenderTargets(AndUnorderedAccessViews)', 'ID3D12GraphicsCommandList::OMSetRenderTargets', 'ID3D12GraphicsCommandList::BeginRenderPass', 'glBindFramebuffer' or 'vkCmdBeginRenderPass'.
		/// </summary>
		set_depth_stencil,
		/// <summary>
		/// Called after 'IDirect3DDevice9::SetRenderTarget', 'ID3D10Device::OMSetRenderTargets', 'ID3D11DeviceContext::OMSetRenderTargets(AndUnorderedAccessViews)', 'ID3D12GraphicsCommandList::OMSetRenderTargets', 'ID3D12GraphicsCommandList::BeginRenderPass', 'glBindFramebuffer' or 'vkCmdBeginRenderPass'.
		/// </summary>
		set_render_target,

		/// <summary>
		/// Called before 'IDirect3DDevice9::DrawPrimitive(UP)', 'ID3D10Device::Draw(Instanced)', 'ID3D11DeviceContext::Draw(Instanced)', 'ID3D12GraphicsCommandList::DrawInstanced', 'gl(Multi)DrawArrays(...)' or 'vkCmdDraw'.
		/// </summary>
		draw,
		/// <summary>
		/// Called before 'IDirect3DDevice9::DrawIndexedPrimitive(UP)', 'ID3D10Device::DrawIndexed(Instanced)', 'ID3D11DeviceContext::DrawIndexed(Instanced)', 'ID3D12GraphicsCommandList::DrawIndexedInstanced', 'gl(Multi)DrawElements(...)' or 'vkCmdDrawIndexed'.
		/// </summary>
		draw_indexed,
		/// <summary>
		/// Called before 'ID3D11DeviceContext::Draw(Indexed)InstancedIndirect', 'ID3D12GraphicsCommandList::ExecuteIndirect', 'gl(Multi)Draw(...)Indirect' or 'vkCmdDraw(Indexed)Indirect'.
		/// </summary>
		draw_indirect,
		/// <summary>
		/// Called before 'ID3D12GraphicsCommandList::ResourceBarrier'.
		/// </summary>
		alias_resource,
		/// <summary>
		/// Called before 'IDirect3DDevice9::Clear', 'ID3D10Device::ClearDepthStencilView', 'ID3D11DeviceContext::ClearDepthStencilView', 'ID3D12GraphicsCommandList::ClearDepthStencilView', 'glClear', 'vkCmdBeginRenderPass' or 'vkCmdClearDepthStencilImage'.
		/// Resource will be in the <see cref="resource_usage::depth_stencil_write"/> state.
		/// </summary>
		clear_depth_stencil,
		/// <summary>
		/// Called before 'IDirect3DDevice9::Clear', 'ID3D10Device::ClearRenderTargetView', 'ID3D11DeviceContext::ClearRenderTargetView', 'ID3D12GraphicsCommandList::ClearRenderTargetView', 'glClear', 'vkCmdBeginRenderPass' or 'vkCmdClearColorImage'.
		/// Resource will be in the <see cref="resource_usage::render_target"/> state.
		/// </summary>
		clear_render_target,

		/// <summary>
		/// Called before 'ID3D12GraphicsCommandList::Reset' or 'vkBeginCommandBuffer' or after 'ID3D11DeviceContext::FinishCommandList'.
		/// </summary>
		reset_command_list,
		/// <summary>
		/// Called before 'ID3D11DeviceContext::ExecuteCommandList', 'ID3D12CommandQueue::ExecuteCommandLists' or 'vkQueueSubmit'.
		/// </summary>
		execute_command_list,
		/// <summary>
		/// Called before 'ID3D12GraphicsCommandList::ExecuteBundle' or 'vkCmdExecuteCommands' or after 'ID3D11DeviceContext::FinishCommandList'.
		/// </summary>
		execute_secondary_command_list,

		/// <summary>
		/// Called before 'IDXGISwapChain::ResizeBuffers' or after updated swap chain via 'vkCreateSwapchainKHR'.
		/// </summary>
		resize,
		/// <summary>
		/// Called before 'IDirect3DDevice9::Present(Ex)', 'IDirect3DSwapChain9::Present', 'IDXGISwapChain::Present(1)', 'wglSwapBuffers' or 'vkQueuePresentKHR'.
		/// </summary>
		present,

		/// <summary>
		/// Called right before ReShade effects are rendered.
		/// </summary>
		reshade_before_effects,
		/// <summary>
		/// Called right after ReShade effects were rendered.
		/// </summary>
		reshade_after_effects,

		num_addon_events
	};

	template <addon_event ev>
	struct addon_event_traits;
	template <>
	struct addon_event_traits<addon_event::init_device> { typedef void(*decl)(api::device *device); };
	template <>
	struct addon_event_traits<addon_event::destroy_device> { typedef void(*decl)(api::device *device); };
	template <>
	struct addon_event_traits<addon_event::init_command_list> { typedef void(*decl)(api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::destroy_command_list> { typedef void(*decl)(api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::init_command_queue> { typedef void(*decl)(api::command_queue *queue); };
	template <>
	struct addon_event_traits<addon_event::destroy_command_queue> { typedef void(*decl)(api::command_queue *queue); };
	template <>
	struct addon_event_traits<addon_event::init_effect_runtime> { typedef void(*decl)(api::effect_runtime *runtime); };
	template <>
	struct addon_event_traits<addon_event::destroy_effect_runtime> { typedef void(*decl)(api::effect_runtime *runtime); };
	template <>
	struct addon_event_traits<addon_event::create_resource> { typedef void(*decl)(api::device *device, api::resource_type type, api::resource_desc *desc); };
	template <>
	struct addon_event_traits<addon_event::create_resource_view> { typedef void(*decl)(api::device *device, api::resource_handle resource, api::resource_view_type type, api::resource_view_desc *desc); };
	template <>
	struct addon_event_traits<addon_event::set_depth_stencil> { typedef void(*decl)(api::command_list *cmd, api::resource_view_handle dsv); };
	template <>
	struct addon_event_traits<addon_event::set_render_target> { typedef void(*decl)(api::command_list *cmd, uint32_t index, api::resource_view_handle rtv); };
	template <>
	struct addon_event_traits<addon_event::draw> { typedef void(*decl)(api::command_list *cmd, uint32_t indices, uint32_t instances); };
	template <>
	struct addon_event_traits<addon_event::draw_indexed> { typedef void(*decl)(api::command_list *cmd, uint32_t vertices, uint32_t instances); };
	template <>
	struct addon_event_traits<addon_event::draw_indirect> { typedef void(*decl)(api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::alias_resource> { typedef void(*decl)(api::command_list *cmd, api::resource_handle old_resource, api::resource_handle new_resource); };
	template <>
	struct addon_event_traits<addon_event::clear_depth_stencil> { typedef void(*decl)(api::command_list *cmd, api::resource_view_handle dsv, uint32_t clear_flags, float depth, uint8_t stencil); };
	template <>
	struct addon_event_traits<addon_event::clear_render_target> { typedef void(*decl)(api::command_list *cmd, api::resource_view_handle rtv, const float color[4]); };
	template <>
	struct addon_event_traits<addon_event::reset_command_list> { typedef void(*decl)(api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::execute_command_list> { typedef void(*decl)(api::command_queue *queue, api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::execute_secondary_command_list> { typedef void(*decl)(api::command_list *cmd, api::command_list *bundle); };
	template <>
	struct addon_event_traits<addon_event::resize> { typedef void(*decl)(api::effect_runtime *runtime, uint32_t width, uint32_t height); };
	template <>
	struct addon_event_traits<addon_event::present> { typedef void(*decl)(api::command_queue *present_queue, api::effect_runtime *runtime); };
	template <>
	struct addon_event_traits<addon_event::reshade_before_effects> { typedef void(*decl)(api::effect_runtime *runtime, api::command_list *cmd); };
	template <>
	struct addon_event_traits<addon_event::reshade_after_effects> { typedef void(*decl)(api::effect_runtime *runtime, api::command_list *cmd); };
}