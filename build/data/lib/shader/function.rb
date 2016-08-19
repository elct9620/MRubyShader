class Shader::Function
  Shader::TYPES.each do |type|
    define_method(type.to_sym) { |*args|
      assert_type(type, *args)
    }
  end

  Shader::FUNCTIONS.each do |function_name|
    define_method(function_name.to_sym) { |*args|
      Node.new(FunctionCall.new(function_name, *args))
    }
  end

  def initialize(return_type, name, parameters = [], &block)
    @return_type = return_type
    @name = name
    @parameters = parameters
    @code = []

    instance_eval(&block)
  end

  def assert_type(name, *args)
    value = args.first
    case value
    when Node
      return Node.new(Type.new(name), *args) unless value.is_variable? && args.size != 1
    end

    Node.new(TypeValue.new(name, *args))
  end

  def is(value)
    AssignNode.new(*value)
  end

  def export_code(type, name, value)
    if type.nil?
      return "#{name} = #{value};"
    end
    "#{type} #{name} = #{value};"
  end

  def method_missing(name, *args, &block)
    value = args.first
    if value.is_a?(AssignNode)
      @code << export_code(value.type, name, value)
    end

    Node.new(Variable.new(name))
  end

  def to_s
    [
      "#{@return_type} #{@name}(#{@parameters.join(", ")}) {",
      @code.join("\n"),
      "}"
    ].join("\n")
  end

end
