﻿char volume_frag[] = "#version 110\n"
                     "\n"
                     "#pragma import_defines(NVIDIA_Corporation)\n"
                     "\n"
                     "uniform sampler3D baseTexture;\n"
                     "uniform float SampleDensityValue;\n"
                     "uniform float TransparencyValue;\n"
                     "uniform float AlphaFuncValue;\n"
                     "\n"
                     "varying vec4 cameraPos;\n"
                     "varying vec4 vertexPos;\n"
                     "varying mat4 texgen;\n"
                     "varying vec4 baseColor;\n"
                     "\n"
                     "void main(void)\n"
                     "{\n"
                     "\n"
                     "    vec4 t0 = vertexPos;\n"
                     "    vec4 te = cameraPos;\n"
                     "\n"
                     "    if (te.x>=0.0 && te.x<=1.0 &&\n"
                     "        te.y>=0.0 && te.y<=1.0 &&\n"
                     "        te.z>=0.0 && te.z<=1.0)\n"
                     "    {\n"
                     "        // do nothing... te inside volume\n"
                     "    }\n"
                     "    else\n"
                     "    {\n"
                     "        if (te.x<0.0)\n"
                     "        {\n"
                     "            float r = -te.x / (t0.x-te.x);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "\n"
                     "        if (te.x>1.0)\n"
                     "        {\n"
                     "            float r = (1.0-te.x) / (t0.x-te.x);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "\n"
                     "        if (te.y<0.0)\n"
                     "        {\n"
                     "            float r = -te.y / (t0.y-te.y);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "\n"
                     "        if (te.y>1.0)\n"
                     "        {\n"
                     "            float r = (1.0-te.y) / (t0.y-te.y);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "\n"
                     "        if (te.z<0.0)\n"
                     "        {\n"
                     "            float r = -te.z / (t0.z-te.z);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "\n"
                     "        if (te.z>1.0)\n"
                     "        {\n"
                     "            float r = (1.0-te.z) / (t0.z-te.z);\n"
                     "            te = te + (t0-te)*r;\n"
                     "        }\n"
                     "    }\n"
                     "\n"
                     "    t0 = t0 * texgen;\n"
                     "    te = te * texgen;\n"
                     "\n"
                     "    const float min_iteratrions = 2.0;\n"
                     "    const float max_iteratrions = 2048.0;\n"
                     "\n"
                     "    float num_iterations = ceil(length((te-t0).xyz)/SampleDensityValue);\n"
                     "\n"
                     "    if (num_iterations<min_iteratrions) num_iterations = min_iteratrions;\n"
                     "    else if (num_iterations>max_iteratrions) num_iterations = max_iteratrions;\n"
                     "    #ifdef NVIDIA_Corporation\n"
                     "    // Recent NVidia drivers have a bug in length() where it throws nan for some values of input into length() so catch these\n"
                     "    else if (num_iterations!=num_iterations) num_iterations = max_iteratrions;\n"
                     "    #endif\n"
                     "\n"
                     "    vec3 deltaTexCoord=(te-t0).xyz/(num_iterations-1.0);\n"
                     "    vec3 texcoord = t0.xyz;\n"
                     "\n"
                     "    vec4 fragColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
                     "    while(num_iterations>0.0)\n"
                     "    {\n"
                     "        vec4 color = texture3D( baseTexture, texcoord);\n"
                     "        float r = color[3]*TransparencyValue;\n"
                     "        if (r>AlphaFuncValue)\n"
                     "        {\n"
                     "            fragColor.xyz = fragColor.xyz*(1.0-r)+color.xyz*r;\n"
                     "            fragColor.w += r;\n"
                     "        }\n"
                     "\n"
                     "        if (fragColor.w<color.w)\n"
                     "        {\n"
                     "            fragColor = color;\n"
                     "        }\n"
                     "        texcoord += deltaTexCoord;\n"
                     "\n"
                     "        --num_iterations;\n"
                     "    }\n"
                     "\n"
                     "    fragColor.w *= TransparencyValue;\n"
                     "    if (fragColor.w>1.0) fragColor.w = 1.0;\n"
                     "\n"
                     "    fragColor *= baseColor;\n"
                     "\n"
                     "    if (fragColor.w<AlphaFuncValue) discard;\n"
                     "    gl_FragColor = fragColor;\n"
                     "}\n"
                     "\n";
