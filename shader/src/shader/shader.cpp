#include "shader/shader.hpp"

Shader::Shader(){
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions (ifstream::failbit | ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		  
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX_SHADER_COMPILATION_FAILED\n\t" << infoLog << endl;
    }else cout << "SHADER::VERTEX_SHADER_COMPILED" << endl;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAGMENT_SHADER_COMPILATION_FAILED\n\t" << infoLog << endl;
    }else cout << "SHADER::FRAGMENT_SHADER_COMPILED" << endl;
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM_LINK_FAILED\n\t" << infoLog << endl;
    }else cout << "SHADER::PROGRAM_LINKED" << endl;
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use(){
    glUseProgram(id);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const string &name, bool value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const string &name, int value) const{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const string &name, float value) const{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const string &name, const vec2 &value) const{
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const string &name, float x, float y) const{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const string &name, const vec3 &value) const{
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string &name, float x, float y, float z) const{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const string &name, const vec4 &value) const{
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const string &name, float x, float y, float z, float w){
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const string &name, const mat2 &mat) const{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const string &name, const mat3 &mat) const{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const string &name, const mat4 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
Shader::~Shader(){

}