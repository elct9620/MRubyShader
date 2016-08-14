require 'lib/uniform'

class Material
  class << self
    @@materials = {}
    @@uniform = ::Uniform.new

    attr_reader :uniform

    def define(name, &block)
      material = Material.new
      material.instance_eval(&block)
      @@materials[name] = material
    end

    def uniform
      @@uniform
    end
  end

end

