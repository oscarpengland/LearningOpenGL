#include "Shader.hpp"

Shader::Shader(const char *vertex_path, const char *fragment_path)
{
    std::string vertex_code;
    std::string fragment_code;
    try
    {
        std::ifstream v_shader_file(vertex_path);
        if (!v_shader_file.is_open()) {
            throw std::runtime_error(std::string("Failed to open vertex shader: ") + vertex_path);
        }

        std::ifstream f_shader_file(fragment_path);
        if (!f_shader_file.is_open()) {
            throw std::runtime_error(std::string("Failed to open fragment shader: ") + fragment_path);
        }
        std::stringstream vertex_stream, fragment_stream;
        vertex_stream << v_shader_file.rdbuf();
        fragment_stream << f_shader_file.rdbuf();
        v_shader_file.close();
        f_shader_file.close();
        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR: Files failed to be read." << e.what() << std::endl;
    }

    const char *v_shader_code = vertex_code.c_str();
    const char *f_shader_code = fragment_code.c_str();

    unsigned int v_shader, f_shader;
    int success;

    v_shader = glCreateShader(GL_VERTEX_SHADER);
    f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(v_shader, 1, &v_shader_code, NULL);
    glCompileShader(v_shader);
    glShaderSource(f_shader, 1, &f_shader_code, NULL);
    glCompileShader(f_shader);

    // Check for shader compilation errors.
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char infolog[512];
        glGetShaderInfoLog(v_shader, 512, NULL, infolog);
        std::cout << "ERROR: Vertex shader failed to compile.\n";
        std::cout << infolog << std::endl;
    }
    
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        char infolog[512];
        glGetShaderInfoLog(f_shader, 512, NULL, infolog);
        std::cout << "ERROR: Fragment shader failed to compile.\n";
        std::cout << infolog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, v_shader);
    glAttachShader(ID, f_shader);
    glLinkProgram(ID);

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);    
}

Shader::~Shader()
{
    if (ID != 0)
    {
        glDeleteProgram(ID);
        ID = 0;
    }
}

Shader::Shader(Shader &&other)
    : ID(other.ID)
{
    other.ID = 0;
}

Shader &Shader::operator=(Shader &&other)
{
    if (this == &other) return *this;

    if (ID != 0) glDeleteProgram(ID);

    ID = other.ID;
    other.ID = 0;
    
    return *this;
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}
void Shader::setMat4(glm::mat4 m, const char *name) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(m));
}
void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}