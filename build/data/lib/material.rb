class Material
  class << self
    @@materials = {}

    def define(name, &block)
      material = Material.new
      material.instance_eval(&block)
      @@materials[name] = material
    end
  end

end

