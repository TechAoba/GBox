#include <GBox.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public GBox::Layer {
public:
    ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
        
        // -------------- Triangle rendering ----------------
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
            0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
            0.0f,   0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };
        GBox::BufferLayout layout = {	
            { GBox::ShaderDataType::Float3, "a_Position" },
            { GBox::ShaderDataType::Float4, "a_Color" }
        };
        unsigned int indices[3] = { 0, 1, 2 };

        m_VertexArray.reset(GBox::VertexArray::Create());
        std::shared_ptr<GBox::VertexBuffer> m_VertexBuffer;
        std::shared_ptr<GBox::IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(GBox::IndexBuffer::Create( indices, sizeof(indices) / sizeof(uint32_t) ));    
        m_VertexBuffer.reset(GBox::VertexBuffer::Create( vertices, sizeof(vertices) ) );

        m_VertexBuffer->SetLayout(layout);      // when we set the layout, we store the layout data in OpenGLBuffer.m_Layout by "SetLayout()" function, then delete layout.
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // -------------- Square rendering ----------------
        float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        GBox::BufferLayout squareLayout = {
            {GBox::ShaderDataType::Float3, "a_Position"}
        };
        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        m_SquareVA.reset(GBox::VertexArray::Create());
        std::shared_ptr<GBox::VertexBuffer> squareVB;
        std::shared_ptr<GBox::IndexBuffer> squareIB;
        squareVB.reset(GBox::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareIB.reset(GBox::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

        squareVB->SetLayout(squareLayout);
        m_SquareVA->AddVertexBuffer(squareVB);
        m_SquareVA->SetIndexBuffer(squareIB);

        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            
            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

        std::string blueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";

        m_Shader.reset(new GBox::Shader(vertexSrc, fragmentSrc));
        m_SquareShader.reset(new GBox::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void OnUpdate(GBox::TimeStep ts) override {
        GBOX_INFO("Delta time: {0}s, ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

        if (GBox::Input::IsKeyPressed(GBOX_KEY_LEFT)) {
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        }
        else if (GBox::Input::IsKeyPressed(GBOX_KEY_RIGHT)) {
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        }
        else if (GBox::Input::IsKeyPressed(GBOX_KEY_UP)) {
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        }
        else if (GBox::Input::IsKeyPressed(GBOX_KEY_DOWN)) {
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        }
        else if (GBox::Input::IsKeyPressed(GBOX_KEY_A)) {
            m_CameraRotation += m_CameraRotateSpeed * ts;
            m_Camera.SetRotation( m_CameraRotation );
        }
        else if (GBox::Input::IsKeyPressed(GBOX_KEY_D)) {
            m_CameraRotation -= m_CameraRotateSpeed * ts;
            m_Camera.SetRotation( m_CameraRotation );
        }

        GBox::RendererCommand::Clear();
        GBox::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

        m_Camera.SetPosition( m_CameraPosition );

        GBox::Renderer::BeginScene(m_Camera);

        glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(0.1f));

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

                GBox::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
            }
        }
        // GBox::Renderer::Submit(m_Shader, m_VertexArray);
        GBox::Renderer::EndScene();
    }

    void OnImGuiRender() {
        
	}

    void OnEvent(GBox::Event& event) override {
        
    }

private:
    std::shared_ptr<GBox::Shader> m_Shader;
    std::shared_ptr<GBox::VertexArray> m_VertexArray;

    std::shared_ptr<GBox::Shader> m_SquareShader;
    std::shared_ptr<GBox::VertexArray> m_SquareVA;

    GBox::OrthograpgicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 1.0f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotateSpeed = 90.0f;
};

class Sandbox : public GBox::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        // PushOverlay(new GBox::ImGuiLayer());     Application.cpp has appended ImGuiLayer
    }
    ~Sandbox() {
        
    }
};

GBox::Application* GBox::CreateApplication() {
    return new Sandbox();
}