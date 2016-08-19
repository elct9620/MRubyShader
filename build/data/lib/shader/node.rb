class Node < Array
  def initialize(*args)
    self.push(*args)
  end

  def is_variable?
    self.first.is_a?(Variable)
  end

  def +(other)
    self.push("+", other)
  end

  def -(other)
    self.push("-", other)
  end

  def *(other)
    self.push("*", other)
  end

  def /(other)
    self.push("/", other)
  end

  def method_missing(name, *args, &block)
    node = self.first
    if node.is_a?(Variable)
      node.send(name, *args)
    end
    self
  end

  def to_s
    "#{self.join(" ")}"
  end
end

class AssignNode < Node
  def type
    return self.first if self.first.is_a?(Type)
    nil
  end

  def to_s
    return super.to_s if type.nil?
    "#{self[1..-1].join(" ")}"
  end
end

class Type
  def initialize(name)
    @name = name
  end

  def to_s
    @name.to_s.downcase
  end
end

class TypeValue
  def initialize(name, *values)
    @name = name
    @values = values
  end

  def expand_values
    @values.map do |node|
      if node.is_a?(Node)
        node.to_s
      else
        node
      end
    end
  end

  def to_s
    "#{@name}(#{expand_values.join(", ")})"
  end
end

class FunctionCall < TypeValue
end

class Variable
  def initialize(name)
    @name = name
    @append = []
  end

  def method_missing(name, *args, &block)
    @append << name
  end

  def to_s
    if @append.size > 0
      return "#{@name.to_s}.#{@append.join(".")}"
    end
    @name.to_s
  end
end

