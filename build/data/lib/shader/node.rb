class Shader::Node
  attr_reader :name

  def initialize(name, *options)
    @name = name
    @options = options || []
    @operates = []
  end

  def <<(other)
    self
  end

  def +(other)
    @operates << "+" << other
    self
  end

  def -(other)
    @operates << "-" << other
    self
  end

  def *(other)
    @operates << "*" << other
    self
  end

  def /(other)
    @operates << "/" << other
    self
  end

  def to_s
    @operates.unshift(" ")
    "#{@name}#{@operates.join(" ")}"
  end
end

class Shader::AssignNode < Shader::Node
  def initialize(type, variable, assigned = false, *options)
    super(name, *options)
    @type = type
    @variable = variable
    @assigned = assigned
  end

  def to_s
    if @assigned
      "#{@variable.name} = #{@variable.value}"
    else
      "#{@type} #{@variable.name} = #{@variable.value}"
    end
  end
end

class Shader::VariableNode < Shader::Node
  def initialize(name, *options)
    super
    @value = []
  end

  def <<(input)
    @value << input
    self
  end

  def value
    @value.join(" ")
  end
end

class Shader::FunctionNode < Shader::Node
  def to_s
    @operates.unshift(" ")
    "#{@name}(#{@options.join(", ")})#{@operates.join(" ")}"
  end
end
