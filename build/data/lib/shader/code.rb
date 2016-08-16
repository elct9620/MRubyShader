class Shader::Code
  TYPES = %i{vec4 vec3 mat4 mat3}
  FUNCTIONS = %i{normalize transpose inverse}

  def initialize
    @varying = []
    @functions = []
    @locals = ["gl_Position"]
  end

  def create_type(name, *args)
    argc = args.size
    case argc
    when 0
      return Node.new(name)
    when 1
      return Node.new("#{name} #{args.first.name} = #{args.first}")
    else
      return Node.new("#{name}(#{args.join(", ")})")
    end
  end

  def create_function(name, *args)

  end

  def input(type, name)
    @locals << name
    @varying << "in #{type} #{name}"
  end

  def output(type, name)
    @locals << name
    @varying << "out #{type} #{name}"
  end

  def uniform(type, name)
    @locals << name
    @varying << "uniform #{type} #{name}"
  end

  def main(&block)
    @functions << Function.new("void", "main", [], @locals, &block)
  end

  def method_missing(name, *args, &block)
    if TYPES.include?(name)
      return create_type(name, *args)
    elsif FUNCTIONS.include?(name)
      return create_function(name, *args)
    else
      # Variable
      return Node.new(name)
    end
  end

  def to_s
    [
      "#version 150",
      @varying.join(";\n") << ";",
      @functions.join("\n")
    ].join("\n")
  end
end
