class Shader::Function < Shader::Code
  def initialize(return_type, name, parameters = [], &block)
    @return_type = return_type
    @name = name
    @parameters = parameters
    @body = []
    instance_eval(&block) if block_given?
  end

  def export(code)
    @body << code
  end

  def to_s
    [
      "#{@return_type} #{@name}(#{@parameters.join}) {",
      "\t" + @body.join("\n\t"),
      "}",
    ].join("\n")
  end
end
