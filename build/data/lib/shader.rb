class Shader
  TYPES = %w{vec4 mat4 vec3 mat3 float sampler2D sampler2DRect}
  FUNCTIONS = %w{normalize transpose inverse max dot reflect pow clamp refract mix texture}
end

require 'lib/shader/node'
require 'lib/shader/function'
require 'lib/shader/code'
require 'lib/shader/shader'
