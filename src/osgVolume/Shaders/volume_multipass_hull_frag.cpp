﻿char volume_multipass_hull_frag[] = "#version 110\n"
                                    "\n"
                                    "uniform sampler2D colorTexture;\n"
                                    "uniform sampler2D depthTexture;\n"
                                    "uniform sampler2D frontFaceDepthTexture;\n"
                                    "uniform vec4 viewportDimensions;\n"
                                    "\n"
                                    "// declare function defined in volume_compute_ray_color.frag\n"
                                    "vec4 computeRayColor(vec4 fragColor, float px, float py, float depth_start, float depth_end);\n"
                                    "\n"
                                    "void main(void)\n"
                                    "{\n"
                                    "    vec2 texcoord = vec2((gl_FragCoord.x-viewportDimensions[0])/viewportDimensions[2], (gl_FragCoord.y-viewportDimensions[1])/viewportDimensions[3]);\n"
                                    "    vec4 color = texture2D( colorTexture, texcoord);\n"
                                    "    float texture_depth = texture2D( depthTexture, texcoord).s;\n"
                                    "    float front_depth = texture2D( frontFaceDepthTexture, texcoord).s;\n"
                                    "\n"
                                    "    // if front_depth is set to the far plane then front\n"
                                    "    // face has been clipped out by the near plane, so assume\n"
                                    "    // front_depth is near plane and reset depth to 0.0\n"
                                    "    if (front_depth==1.0) front_depth = 0.0;\n"
                                    "\n"
                                    "    if (gl_FragCoord.z<texture_depth)\n"
                                    "    {\n"
                                    "        // fragment starts infront of all other scene objects\n"
                                    "\n"
                                    "        gl_FragDepth = front_depth; // gl_FragCoord.z;\n"
                                    "\n"
                                    "        vec4 ray_color = computeRayColor(vec4(0.0,0.0,0.0,0.0), gl_FragCoord.x, gl_FragCoord.y, gl_FragCoord.z, front_depth);\n"
                                    "\n"
                                    "        gl_FragColor = mix(color, ray_color, ray_color.a);\n"
                                    "    }\n"
                                    "    else\n"
                                    "    {\n"
                                    "        // fragment starts behind other scene objects\n"
                                    "        discard;\n"
                                    "\n"
                                    "        if (front_depth<texture_depth)\n"
                                    "        {\n"
                                    "            gl_FragDepth = front_depth;\n"
                                    "        }\n"
                                    "        else\n"
                                    "        {\n"
                                    "            gl_FragDepth = texture_depth;\n"
                                    "        }\n"
                                    "\n"
                                    "        if (color.a<1.0)\n"
                                    "        {\n"
                                    "            // need to blend ray behind objects with object color and then with the ray from the object depth to the eye point\n"
                                    "\n"
                                    "            if (front_depth<texture_depth)\n"
                                    "            {\n"
                                    "                vec4 front_ray_color = computeRayColor(vec4(0.0,0.0,0.0,0.0), gl_FragCoord.x, gl_FragCoord.y, texture_depth, front_depth);\n"
                                    "                // front_ray_color *= vec4(0.0,0.0,1.0,1.0);\n"
                                    "                if (front_ray_color.a<1.0)\n"
                                    "                {\n"
                                    "                    if (color.a<1.0)\n"
                                    "                    {\n"
                                    "                        vec4 back_ray_color = computeRayColor(vec4(0.0,0.0,0.0,0.0), gl_FragCoord.x, gl_FragCoord.y, gl_FragCoord.z, texture_depth);\n"
                                    "                        // back_ray_color *= vec4(0.0,1.0,0.0,1.0);\n"
                                    "                        color = mix(back_ray_color, color, color.a);\n"
                                    "                    }\n"
                                    "                    gl_FragColor = mix(color, front_ray_color, front_ray_color.a);\n"
                                    "                }\n"
                                    "                else\n"
                                    "                {\n"
                                    "                    gl_FragColor = front_ray_color;\n"
                                    "                }\n"
                                    "            }\n"
                                    "            else\n"
                                    "            {\n"
                                    "                vec4 back_ray_color = computeRayColor(vec4(0.0,0.0,0.0,0.0), gl_FragCoord.x, gl_FragCoord.y, gl_FragCoord.z, front_depth);\n"
                                    "                // back_ray_color *= vec4(0.0,1.0,1.0,1.0);\n"
                                    "                gl_FragColor = mix(back_ray_color, color, color.a);\n"
                                    "            }\n"
                                    "        }\n"
                                    "        else\n"
                                    "        {\n"
                                    "            // main scene fragment is opaque so no blending required with ray beyond scene depth\n"
                                    "\n"
                                    "            // if the front face depth is behind the depth in the main scene\n"
                                    "            if (front_depth>texture_depth) discard;\n"
                                    "\n"
                                    "            // gl_FragDepth = texture_depth;\n"
                                    "\n"
                                    "            // need to blend the object color with the ray from the object depth to the eye point\n"
                                    "            vec4 ray_color = computeRayColor(vec4(0.0,0.0,0.0,0.0), gl_FragCoord.x, gl_FragCoord.y, texture_depth, front_depth);\n"
                                    "            // ray_color *= vec4(1.0,1.0,0.0,1.0);\n"
                                    "            gl_FragColor = mix(color, ray_color, ray_color.a);\n"
                                    "        }\n"
                                    "    }\n"
                                    "\n"
                                    "}\n"
                                    "\n";
