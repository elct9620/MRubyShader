class UnityChanShader
  def initialize
    @shader = Shader.new

    @shader.vertex do
      input Vec4, :position
      input Vec4, :normal
      input Vec2, :texcoord

      output Vec4, :lightIntensity

      uniform Mat4, :modelViewProjectionMatrix
      uniform Mat4, :modelViewMatrix
      uniform Mat4, :modelMatrix
      uniform Mat4, :textureMatrix

      uniform Vec3, :lightColor
      uniform Sampler2DRect, :tex0
      uniform Vec2, :tex0Scale # Fix texcoord is normalized, but texture didn't work with this
      uniform Sampler2DRect, :normalMap
      uniform Vec2, :normalMapScale
      uniform Sampler2DRect, :spec
      uniform Vec2, :specScale

      uniform Vec3, :mousePosition

      main do
        lightPosition is Vec4 vec4(mousePosition.x, mousePosition.y, -1000, 1)
        diffuseReflect is Vec4 vec4(1) # Diffuse Reflect Color
        normalMatrix is Mat4 transpose(inverse(modelViewMatrix)) # Normal is vertical model

        nm is Vec4 texture(normalMap, texcoord * normalMapScale)
        specColor is Vec4 texture(spec, texcoord * specScale)

        v is Vec4 modelViewMatrix * position
        n is Vec4 normalize(nm)
        l is Vec4 normalize(lightPosition - v)

        refectVec is Vec4 normalize(reflect(lightPosition, nm) * -1)
        specVec is float, pow(max(dot(refectVec, normalize(v)), 0), specColor.r)

        amb is Vec4 vec4(0.6) # Environment Color
        diff is Vec4 diffuseReflect * vec4(lightColor * vec3(0.01), 1) * max(dot(n, l), 0)
        diff is clamp(diff, 0, 1)

        lightIntensity is (diff + amb + specVec) * texture(tex0, texcoord * tex0Scale)

        gl_Position is modelViewProjectionMatrix * position
      end
    end

    @shader.fragment do
      output Vec4, :outputColor
      input Vec4, :lightIntensity

      main do
        outputColor is vec4(lightIntensity.xyz, 1)
      end
    end

    @shader.bind.apply
  end

  def draw(&block)
    @shader.draw(&block)
  end

  def color=(color)
    @shader.set_vector3d("lightColor", color)
  end

  def mouse=(mouse)
    @shader.set_vector3d("mousePosition", mouse)
  end

  def texture=(texture)
    @shader.set_texture("tex0", texture, 1)
  end

  def normalmap=(texture)
    @shader.set_texture("normalMap", texture, 2)
  end

  def spec=(texture)
    @shader.set_texture("spec", texture, 3)
  end
end
