module Shader::NumberCalculable
  def +(other)
    return Shader::NumberNode.new(self) + other if other.is_a?(Shader::Calculable)
    super
  end

  def -(other)
    return Shader::NumberNode.new(self) - other if other.is_a?(Shader::Calculable)
    super
  end

  def *(other)
    return Shader::NumberNode.new(self) * other if other.is_a?(Shader::Calculable)
    super
  end

  def /(other)
    return Shader::NumberNode.new(self) / other if other.is_a?(Shader::Calculable)
    super
  end
end

class Fixnum
  prepend Shader::NumberCalculable
end

class Float
  prepend Shader::NumberCalculable
end
