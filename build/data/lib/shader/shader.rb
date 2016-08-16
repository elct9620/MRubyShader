class Shader
  def vertex(&block)
    @vertex ||= Code.new
    @vertex.instance_eval(&block)
    self.vertex = @vertex.to_s
    puts "Vertex Shader ====>"
    puts @vertex
  end

  def fragment(&block)
    @fragment ||= Code.new
    @fragment.instance_eval(&block)
    self.fragment = @fragment.to_s
    puts "Fragment Shader ====>"
    puts @fragment
  end
end
