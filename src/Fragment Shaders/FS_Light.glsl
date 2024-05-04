#version 330
//Colors
uniform float theta;
out vec4 FragColor;

float ka = 0.5;
float kd = 0.8;
float ks = 5;
float sh = 30;

vec4 object_color = vec4(1,0.3,0.5,1);
vec4 light_color = vec4(0.5,0.8,0.1,1);

in vec3 v;
in vec3 n;
in vec3 l;
in vec3 h;

uniform mat4 modelViewMatrix;  // Camera view matrix
uniform int conditionIndex;

vec3 rainbow(float hue)
{
    float h = hue * 6.0;
    float i = floor(h);
    float f = h - i;
    float p = 1.0 - 1.0;
    float q = 1.0 - f;
    float t = 1.0 - (1.0 - f);

    if (i == 0.0) return vec3(1.0, t, p);
    else if (i == 1.0) return vec3(q, 1.0, p);
    else if (i == 2.0) return vec3(p, 1.0, t);
    else if (i == 3.0) return vec3(p, q, 1.0);
    else if (i == 4.0) return vec3(t, p, 1.0);
    else return vec3(1.0, p, q);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
    vec4 lightIntencity = ka * light_color +
                           kd * max(dot(l, n), 0) * light_color +
                           ks * max(pow(dot(h, n), sh), 0) * vec4(1, 1, 1, 1);

    if (conditionIndex == 0) {
        FragColor = object_color * lightIntencity;
    }

    else if(conditionIndex == 1)
    {
        vec2 c = vec2(gl_FragCoord.x / 300.0 - 1.5, gl_FragCoord.y / 300.0 - 1.0);
        vec2 z = c;
        int n;

        for (n = 0; n < 100; n++)
        {
            if (length(z) > 2.0)
                break;

            float xtemp = z.x * z.x - z.y * z.y + c.x;
            z.y = 2.0 * z.x * z.y + c.y;
            z.x = xtemp;
        }

        float hue = mod(float(n) + theta * 10.0, 100.0) / 100.0;
        vec3 color = rainbow(hue);
    
        // Use a gradient of colors based on the iteration count
        float gradient = float(n) / 100.0;
        FragColor = vec4(color * gradient, 1.0)* lightIntencity;
    }

    else if(conditionIndex == 2)
    {
        vec2 c = vec2(gl_FragCoord.x / 300.0 - 1.5, gl_FragCoord.y / 300.0 - 1.0);
        vec2 z = c;
        int n;

        float hue = mod(float(n) + theta * 10.0, 100.0) / 100.0;

        // Convert hue to RGB using HSV to RGB conversion
        vec3 rgb = hsv2rgb(vec3(hue, 1.0, 1.0));

        FragColor = vec4(rgb, 1.0) * lightIntencity;
    }

    else if(conditionIndex == 3)
    {
        // Calculate polar coordinates
        float phi = acos(2.0 * gl_FragCoord.y / 600.0 - 1.0);
        float theta = atan(gl_FragCoord.x / 600.0 - 0.5, gl_FragCoord.z / 600.0 - 0.5) + 3.1415926535897932384626433832795;

        // Use UV coordinates to determine color
        vec3 color;

        // Assign different colors based on theta range
        if (theta < 0.2 * 3.1415926535897932384626433832795) {
            color = vec3(1.0, 0.0, 0.0);  // Red
        } else if (theta < 0.4 * 3.1415926535897932384626433832795) {
            color = vec3(1.0, 0.5, 0.0);  // Orange
        } else if (theta < 0.6 * 3.1415926535897932384626433832795) {
            color = vec3(1.0, 1.0, 0.0);  // Yellow
        } else if (theta < 0.8 * 3.1415926535897932384626433832795) {
            color = vec3(0.0, 1.0, 0.0);  // Green
        } else {
            color = vec3(0.0, 0.0, 1.0);  // Blue
        }

        FragColor = vec4(color, 1.0) * lightIntencity;
    }

    else if(conditionIndex == 4)
    {
        vec4 worldPos = modelViewMatrix * vec4(gl_FragCoord.x / 300.0 - 1.5, gl_FragCoord.y / 300.0 - 1.0, 0.0, 1.0);
        vec2 c = worldPos.xy;
        int n;

        // Calculate angle for rainbow colors
        float angle = atan(c.y, c.x);
        float hue = (angle + 3.14159265359) / (2.0 * 3.14159265359);

        // Smoothly transition colors over time
        hue += theta * 0.1;
        hue = fract(hue);

        // Convert HSV to RGB
        float cVal = 1.0;
        float x = cVal * (1.0 - abs(mod(hue * 6.0, 2.0) - 1.0));
        float m = 0.0;

        vec3 rgb;
        if (hue < 1.0 / 6.0)
            rgb = vec3(cVal, x, 0.0);
        else if (hue < 2.0 / 6.0)
            rgb = vec3(x, cVal, 0.0);
        else if (hue < 3.0 / 6.0)
            rgb = vec3(0.0, cVal, x);
        else if (hue < 4.0 / 6.0)
            rgb = vec3(0.0, x, cVal);
        else if (hue < 5.0 / 6.0)
            rgb = vec3(x, 0.0, cVal);
        else
            rgb = vec3(cVal, 0.0, x);

        // Apply final color to fragment
        FragColor = vec4(rgb, 1.0);
    }
}