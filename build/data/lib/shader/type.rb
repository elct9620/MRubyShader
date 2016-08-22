class Shader::Type
  def initialize(type, *args)
    @type = type
    @args = args
  end

  def to_typename
    TYPES[@type]
  end

  def to_typevalue
    return "#{@type}(#{@args.join(", ")})" if TYPE_VALUES[@type].nil?
    TYPE_VALUES[@type].call(*args)
  end

  def to_s
    to_typevalue
  end
end

class Shader::Variable
  include Calculable

  def initialize(name)
    @name = name
    @suffix = []
  end

  def -@
    @name = "-#{@name}"
  end

  def method_missing(name, *args, &block)
    @suffix << name
    self
  end

  def to_s
    return "#{@name}" if @suffix.empty?
    "#{@name}.#{@suffix.join(".")}"
  end
end

class Shader::FunctionCall < Shader::Variable
  def initialize(name, *args)
    super(name)
    @args = args
  end

  def to_funtion
    "#{@name}(#{@args.join(", ")})"
  end

  def to_s
    return "#{to_funtion}" if @suffix.empty?
    "#{to_funtion}.#{@suffix.join(".")}"
  end
end
