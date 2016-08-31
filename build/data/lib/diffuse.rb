class DiffuseShader
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
      uniform Vec3, :mousePosition

      main do
        diffuseReflect is Vec4 vec4(1) # Diffuse Reflect Color
        normalMatrix is Mat4 transpose(inverse(modelViewMatrix)) # Normal is vertical model

        v is Vec4 modelViewMatrix * position
        lightPosition is Vec4 vec4(mousePosition.x, mousePosition.y, 0, 1)
        n is Vec4 normalize(normalMatrix * normal)
        l is Vec4 normalize(lightPosition - v)

        amb is Vec4 vec4(0.1) # Environment Color
        diff is Vec4 diffuseReflect * vec4(lightColor * vec3(10), 1) * max(dot(n, l), 0)
        diff is clamp(diff, 0, 1)

        lightIntensity is diff + amb

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
end
