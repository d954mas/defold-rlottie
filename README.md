# Defold Rlottie

Rlottie native extension defold

Rlottie is a platform independent standalone c++ library for rendering vector based animations and art in realtime.

Lottie loads and renders animations and vectors exported in the bodymovin JSON format. Bodymovin JSON can be created and exported from After Effects with bodymovin, Sketch with Lottie Sketch Export, and from Haiku.
More info about Rlottie: https://github.com/Samsung/rlottie

Rlottie draw animation in buffer. So it is slow.

## Installation

You can use Rlottie in your own project by adding this project as a Defold library dependency. Open your game.project file and in the dependencies field under project add:

https://github.com/d954mas/defold-rlottie/archive/master.zip

Or point to the ZIP file of a specific release.

## API
```lua
--create defold buffer
--rlottie support only ARGB8888
local w,h = 1000,1000
local rlottie_buffer = buffer.create(w * h, -- size of the buffer width*height
    {{
       name = hash("my_buffer"),
       type = buffer.VALUE_TYPE_UINT8,
       count = 4
     }})
     
--create surface.Will draw animation in that surface     
local surface = rlottie.surface_create(w,h,rlottie_buffer) 

--create animation
---@param data string data json
---@param key string key for animation cache
---@param use_cache boolean
local anim = rlottie.animation_load_from_data(data,key,use_cache)

local size = anim.size()
local duration = animation.duration()
local frameRate = animation.frameRate()
local totalFramesize = animation.totalFrame()

---@param a [0,1]
local frameAtPos = animation.frameAtPos(a)

---@param frame number
---@param surface RlottieSurface
---@param keep_aspect boolean
animation.renderSync(frame,surface,keep_aspect)


---change texture for buffer texture
local resource_path = go.get("#sprite", "texture0")
local header = {
		width = w,
		height = h,
		type = resource.TEXTURE_TYPE_2D,
		format = resource.TEXTURE_FORMAT_RGBA,
		num_mip_maps = 1
}
resource.set_texture(resource_path, header, buffer)
```
Be careful when change texture for sprite or model. You do not change texture for only that object.

You get path to texture and rewrite that texture. All other object that use that texture also will be changed

https://forum.defold.com/t/change-model-texture-in-runtime/10952/11 .

Also do not change texture for sprite if it use atlas. Because sprite will be use uv for that region, not for full texture


 
## Demo

https://d954mas.github.io/defold-rlottie/

## Problems

1)Rlottie draw animation in buffer. So it is slow.

2)Some lottie animations have problems.

3)Do not support separate images for json data.All images must be embedded in json.

4)Not full rlottie api exported in defold. I add api that i need. I will be add other when i need them. So if you need some api you should add it by yourself.

---
