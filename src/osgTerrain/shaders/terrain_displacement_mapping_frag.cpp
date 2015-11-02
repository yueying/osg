﻿char terrain_displacement_mapping_frag[] = "#pragma import_defines ( TEXTURE_2D, TEXTURE_WEIGHTS, COLOR_LAYER0, COLOR_LAYER1, COLOR_LAYER2)\n"
                                           "\n"
                                           "\n"
                                           "#if defined(TEXTURE_2D) && defined(COLOR_LAYER0)\n"
                                           "uniform sampler2D colorTexture0;\n"
                                           "#endif\n"
                                           "\n"
                                           "#if defined(TEXTURE_2D) && defined(COLOR_LAYER1)\n"
                                           "uniform sampler2D colorTexture1;\n"
                                           "#endif\n"
                                           "\n"
                                           "#if defined(TEXTURE_2D) && defined(COLOR_LAYER2)\n"
                                           "uniform sampler2D colorTexture2;\n"
                                           "#endif\n"
                                           "\n"
                                           "\n"
                                           "#if defined(TEXTURE_2D) && defined(TEXTURE_WEIGHTS)\n"
                                           "uniform float TextureWeights[];\n"
                                           "#define WEIGHTS_LOOKUP(i) TextureWeights[i]\n"
                                           "#else\n"
                                           "#define WEIGHTS_LOOKUP(i) 1.0\n"
                                           "#endif\n"
                                           "\n"
                                           "varying vec2 texcoord;\n"
                                           "varying vec4 basecolor;\n"
                                           "\n"
                                           "void main(void)\n"
                                           "{\n"
                                           "#ifdef TEXTURE_2D\n"
                                           "    vec4 color = vec4(0.0, 0.0, 0.0, 0.0);\n"
                                           "\n"
                                           "    #ifdef COLOR_LAYER0\n"
                                           "        color = color + texture2D( colorTexture0, texcoord)*WEIGHTS_LOOKUP(0);\n"
                                           "    #endif\n"
                                           "\n"
                                           "    #ifdef COLOR_LAYER1\n"
                                           "        color = color + texture2D( colorTexture1, texcoord)*WEIGHTS_LOOKUP(1);\n"
                                           "    #endif\n"
                                           "\n"
                                           "    #ifdef COLOR_LAYER2\n"
                                           "        color = color + texture2D( colorTexture2, texcoord)*WEIGHTS_LOOKUP(2);\n"
                                           "    #endif\n"
                                           "\n"
                                           "    gl_FragColor = basecolor * color;\n"
                                           "#else\n"
                                           "    gl_FragColor = basecolor;\n"
                                           "#endif\n"
                                           "}\n"
                                           "\n";
