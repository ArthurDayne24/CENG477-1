#version 410

layout(location = 0) in vec3 position;

// Data from CPU 
uniform mat4 MVP; // ModelViewProjection Matrix
uniform mat4 MV; // ModelView idMVPMatrix
uniform mat4 normalMatrix;
uniform vec4 cameraPosition;
uniform float heightFactor;

// Texture-related data
uniform sampler2D rgbTexture;
uniform int widthTexture;
uniform int heightTexture;


// Output to Fragment Shader
out vec2 textureCoordinate; // For texture-color
out vec3 vertexNormal; // For Lighting computation
out vec3 ToLightVector; // Vector from Vertex to Light;
out vec3 ToCameraVector; // Vector from Vertex to Camera;

vec3 lightPosition = vec3(widthTexture/2, widthTexture + heightTexture, heightTexture/2);


void main()
{

    vec3 tempPos = position;
    // get texture value, compute height
    textureCoordinate = vec2(1 - (float(position.x) / (widthTexture+1)), 1 - (float(position.z) / (heightTexture+1)));

    vec4 textureColor = texture(rgbTexture, textureCoordinate);
    vec3 rgb = textureColor.xyz;

    tempPos.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);
    // compute normal vector using also the heights of neighbor vertices
    vec2 neighborTexCoord;
    vec3 tempNormal;

    if(position.x == 0 && position.z == heightTexture - 1) { // For left bottom vertex
        vec3 neighbor1 = vec3(position.x + 1, 0, position.z);
        vec3 neighbor2 = vec3(position.x + 1, 0, position.z - 1);
        vec3 neighbor3 = vec3(position.x , 0, position.z - 1);

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor3.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor3.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor3.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = neighbor1 - tempPos;
        vec3 v2 = neighbor2 - tempPos;
        vec3 v3 = neighbor3 - tempPos;

        vec3 upLeftTriangleNormal = cross(v2,v1);
        vec3 bottomRightTriangleNormal = cross(v3, v2);

        tempNormal = normalize(upLeftTriangleNormal + bottomRightTriangleNormal);
    }
    else if(position.x == widthTexture - 1 && position.z == heightTexture - 1) {  // For right bottom vertex
        vec3 neighbor1 = vec3(position.x - 1, 0, position.z);
        vec3 neighbor2 = vec3(position.x, 0, position.z - 1);

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = tempPos - neighbor1;
        vec3 v2 = neighbor2 - neighbor1;

        tempNormal = normalize(cross(v1, v2));

    }
    else if(position.x == widthTexture - 1 && position.z == 0) { // For top right vertex
        vec3 neighbor1 = vec3(position.x - 1, position.y, position.z);
        vec3 neighbor2 = vec3(position.x - 1, position.y, position.z + 1);
        vec3 neighbor3 = vec3(position.x , 0, position.z+1);

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor3.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor3.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor3.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = neighbor1 - tempPos;
        vec3 v2 = neighbor2 - tempPos;
        vec3 v3 = neighbor3 - tempPos;

        vec3 leftTriangleNormal = cross(v1,v2);
        vec3 bottomTriangleNormal = cross(v2,v3);

        tempNormal = normalize(leftTriangleNormal + bottomTriangleNormal);
    }
    else if(position.x == 0 && position.z == 0) { // top left vertex
        vec3 neighbor1 = vec3(position.x + 1, position.y, position.z);
        vec3 neighbor2 = vec3(position.x, position.y, position.z + 1);

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = tempPos - neighbor1;
        vec3 v2 = neighbor2 - neighbor1;

        tempNormal = normalize(cross(v1, v2));
    } else if(((position.z == 0 || position.z == heightTexture-1)  && position.x > 0) || ((position.x == 0 || position.x == widthTexture - 1) && position.z > 0)) {
        vec3 neighbor1, neighbor2, neighbor3, neighbor4;
        if(position.z == heightTexture - 1) { // Between bottom left and right vertices
            neighbor1 = vec3(position.x - 1, 0 , position.z);
            neighbor2 = vec3(position.x , 0 , position.z - 1);
            neighbor3 = vec3(position.x + 1 , 0 , position.z - 1);
            neighbor4 = vec3(position.x + 1, 0 , position.z);
        } else if(position.z == 0){ // Between top left and top vertices
            neighbor1 = vec3(position.x + 1, 0 , position.z);
            neighbor2 = vec3(position.x , 0 , position.z + 1);
            neighbor3 = vec3(position.x - 1 , 0 , position.z + 1);
            neighbor4 = vec3(position.x - 1, 0 , position.z);
        } else if(position.x == 0){ // Between bottom left and top left vertices
            neighbor4 = vec3(position.x, 0 , position.z + 1);
            neighbor3 = vec3(position.x + 1, 0 , position.z);
            neighbor2 = vec3(position.x + 1 , 0 , position.z - 1);
            neighbor1 = vec3(position.x, 0 , position.z - 1);
        } else if(position.x == widthTexture - 1) {  // Between bottom right and top right vertices
            neighbor4 = vec3(position.x, 0 , position.z - 1);
            neighbor3 = vec3(position.x - 1, 0 , position.z);
            neighbor2 = vec3(position.x - 1 , 0 , position.z + 1);
            neighbor1 = vec3(position.x, 0 , position.z + 1);
        }

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor3.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor3.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor3.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor4.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor4.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor4.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = neighbor1 - tempPos;
        vec3 v2 = neighbor2 - tempPos;
        vec3 v3 = neighbor3 - tempPos;
        vec3 v4 = neighbor4 - tempPos;

        vec3 leftTriangleNormal = cross(v2,v1);
        vec3 rightTopTriangleNormal = cross(v3,v2);
        vec3 rightBottomTriangleNormal = cross(v4,v3);

        tempNormal = normalize(leftTriangleNormal + rightTopTriangleNormal + rightBottomTriangleNormal);
    }
    else { // All cases in the middle i.e 6 neighbors for each vertices
        vec3 neighbor1 = vec3(position.x - 1, 0 , position.z);  // West of the vertex
        vec3 neighbor2 = vec3(position.x - 1 , 0 , position.z + 1); // Southwest of the vertex
        vec3 neighbor3 = vec3(position.x , 0 , position.z + 1); // South of the vertex
        vec3 neighbor4 = vec3(position.x + 1 , 0 , position.z); // East of the vertex
        vec3 neighbor5 = vec3(position.x + 1, 0 , position.z - 1); // Northeast of the vertex
        vec3 neighbor6 = vec3(position.x , 0 , position.z - 1); // North of the vertex

        neighborTexCoord.x = abs(neighbor1.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor1.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor1.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor2.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor2.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor2.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor3.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor3.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor3.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor4.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor4.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor4.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor5.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor5.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor5.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        neighborTexCoord.x = abs(neighbor6.x-widthTexture)/widthTexture;
        neighborTexCoord.y = abs(neighbor6.z-heightTexture)/heightTexture;
        textureColor = texture(rgbTexture, neighborTexCoord);
        rgb = textureColor.xyz;
        neighbor6.y = heightFactor*(0.2126*rgb.x + 0.7152*rgb.y + 0.0722*rgb.z);

        vec3 v1 = neighbor1 - tempPos;
        vec3 v2 = neighbor2 - tempPos;
        vec3 v3 = neighbor3 - tempPos;
        vec3 v4 = neighbor4 - tempPos;
        vec3 v5 = neighbor5 - tempPos;
        vec3 v6 = neighbor6 - tempPos;

        vec3 t1normal = cross(v1,v2);
        vec3 t2normal = cross(v2,v3);
        vec3 t3normal = cross(v3,v4);
        vec3 t4normal = cross(v4,v5);
        vec3 t5normal = cross(v5,v6);
        vec3 t6normal = cross(v6,v1);

        tempNormal = normalize(t1normal + t2normal + t3normal + t4normal +  t5normal + t6normal);
    }

    // compute toLight vector vertex coordinate in VCS
    ToLightVector = normalize(vec3(MV*vec4(lightPosition - tempPos, 0)));
    ToCameraVector = normalize(vec3(MV*(vec4(vec3(cameraPosition) - tempPos, 0))));
    vertexNormal = normalize(vec3(normalMatrix*vec4(tempNormal,0)));

    // set gl_Position variable correctly to give the transformed vertex position
    gl_Position = MVP*vec4(tempPos,1); // this is a placeholder. It does not correctly set the position
    
}
