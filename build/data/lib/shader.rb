class Shader
  TYPES = %w{vec4 mat4 vec3 mat3 sampler}
  FUNCTIONS = %w{normalize transpose inverse max dot reflect pow clamp}
end

require 'lib/shader/node'
require 'lib/shader/function'
require 'lib/shader/code'
require 'lib/shader/shader'
