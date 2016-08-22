module Shader::Calculable
  def operation
    @operation ||= []
  end

  def +(other)
    operation.push("+", other)
    BracketsNode.new(self)
  end

  def -(other)
    operation.push("-")
    operation.push(other) unless other.nil?
    BracketsNode.new(self)
  end

  def *(other)
    operation.push("*", other)
    BracketsNode.new(self)
  end

  def /(other)
    operation.push("/", other)
    BracketsNode.new(self)
  end

  def expanded_operation
    operation.map do |node|
      if node.respond_to?(:to_expression)
        node.to_expression
      else
        node.to_s
      end
    end
  end

  def to_expression
    return to_s if operation.empty?
    "#{to_s} #{expanded_operation.join(" ")}"
  end
end

class Shader::AssignNode
  def initialize(type, *args)
    @type = type
    @expression = args.shift

    unless type.is_a?(Type) && !@expression.nil?
      @expression = @type
      @type = nil
    end
  end

  def expression
    return @expression.to_expression if @expression.respond_to?(:to_expression)
    @expression
  end

  def is_const?(name)
    ("A".."Z").include?(name.to_s[0])
  end

  def to(name)
    name = "-#{name}" if @negative
    return "#{name} = #{expression};" if @type.nil?
    return "#{@type.to_typename} #{name} = #{expression};" unless is_const?(name)
    "const #{@type.to_typename} #{name} = #{expression};"
  end

  def to_s
    to(nil)
  end
end

class Shader::ExpressionNode
  include Calculable
end

class Shader::NumberNode
  include Calculable

  def initialize(value)
    @value = value
  end

  def to_s
    @value.to_s
  end
end

class Shader::BracketsNode
  include Calculable

  def initialize(content)
    @content = content
  end

  def to_s
    return "(#{@content.to_expression})" if @content.respond_to?(:to_expression)
    "(#{@content.to_s})"
  end
end
