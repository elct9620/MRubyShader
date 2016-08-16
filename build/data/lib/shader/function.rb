class Shader::Function
  TYPES = %i{vec4 vec3 mat4 mat3}
  FUNCTIONS = %i{normalize transpose inverse max dot}

  def initialize(return_type, name, parameters = nil, globals = [], &block)
    @return_type = return_type
    @name = name
    @parameters = parameters || []
    @body = []
    @globals = globals
    @locals = []
    instance_eval(&block) if block_given?
  end

  def vairable_exists?(name)
    @globals.include?(name) || @locals.include?(name)
  end

  def create_type(name, *args)
    argc = args.size
    case argc
    when 0
      return Node.new(name)
    when 1
      assigned = vairable_exists?(args.first.name.to_s)
      @locals << args.first.name.to_s unless assigned
      statment = AssignNode.new(name, args.first, assigned)
      @body << statment
      return statment
    else
      return Node.new("#{name}(#{args.join(", ")})")
    end
  end

  def create_function(name, *args)
    return FunctionNode.new(name, *args)
  end

  def method_missing(name, *args, &block)
    if TYPES.include?(name)
      return create_type(name, *args)
    elsif FUNCTIONS.include?(name)
      return create_function(name, *args)
    else
      # Variable
      return VariableNode.new(name)
    end
  end


  def to_s
    [
      "#{@return_type} #{@name}(#{@parameters.join(", ")}) {",
      @body.join(";\n") << ";",
        "}"
    ].join("\n")
  end
end
