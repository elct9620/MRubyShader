# Default Class
class Shader
  TYPES = {
    vec2: "vec2",
    vec3: "vec3",
    vec4: "vec4",
    mat3: "mat3",
    mat4: "mat4",
    float: "float",
    sampler2d: "sampler2D",
    sampler2D: "sampler2D",
    sampler2drect: "sampler2DRect",
    sampler2DRect: "sampler2DRect"
  }

  TYPE_VALUES = {
    # Special Type should provide special convert feature
    float: -> (*args) { args.first }
  }

  VARYING = {
    input: "in",
    output: "out",
    uniform: "uniform",
    varying: "varying"
  }

  FUNCTIONS = %w{
    max
    dot
    pow
    mix
    clamp
    inverse
    reflect
    refract
    texture
    transpose
    normalize
  }
end

require 'lib/shader/node'
require 'lib/shader/type'
require 'lib/shader/code'
require 'lib/shader/function'
require 'lib/shader/number'

# DSL
class Shader
  def vertex(&block)
    code = Code.new
    code.instance_eval(&block)
    puts "===== Vertex Shader =====>", code.to_s # For Debug
    self.vertex = code.to_s
  end

  def fragment(&block)
    code = Code.new
    code.instance_eval(&block)
    puts "===== Fragment Shader =====>", code.to_s
    self.fragment = code.to_s
  end
end
