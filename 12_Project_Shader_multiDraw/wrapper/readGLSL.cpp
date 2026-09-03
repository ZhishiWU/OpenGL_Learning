#include <readGLSL.h>

string readGLSL(const char *filename)
{
    string shaderCode;
    ifstream file(filename, ios::in);

    if (!file.is_open())
        cout << "Failed to load shader: " << filename << endl;

    string line;
    line = "";

    while (!file.eof())
    {
        getline(file, line);
        shaderCode.append(line + "\n");
    }

    file.close();

    return shaderCode;
}