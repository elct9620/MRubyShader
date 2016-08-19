class Shader::Code
  IO_KEYWORDS = %w{input output uniform}

  Shader::TYPES.each do |type|
    define_method(type.to_sym) { type }
  end

  IO_KEYWORDS.each do |keyword|
    define_method(keyword.to_sym) do |type, name|
      keyword = "in" if keyword.to_s == "input"
      keyword = "out" if keyword.to_s == "output"
      @varying << "#{keyword} #{type} #{name};"
    end
  end

  def initialize
    @varying = []
    @functions = []
    @locals = []
  end

  def create_function(name, *args)

  end

  def main(&block)
    @functions << Function.new("void", "main", [], &block)
  end

  def method_missing(name, *args, &block)
    name.to_s
  end

  def to_s
    [
      "#version 150",
      @varying.join("\n"),
      @functions.join("\n")
    ].join("\n")
  end
end
