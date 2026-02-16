cbuffer VignetteParams : register(b0)
{
    float2 center; // Center of vignette effect (normalized, default 0.5, 0.5)
    float intensity; // Intensity of vignette effect (0.0 - 1.0)
    float radius; // Radius where the effect begins (0.0 - 1.0)
    float smoothness; // Smoothness of the transition (0.0 - 1.0)
    float screenAspect; // Aspect ratio of the screen
    float saturation; // 1.0 = neutral
    float brightness; // 1.0 = neutral
    float contrast;   // 1.0 = neutral
    float hdrBoost;   // 0.0 = off
    float hdrOutputEnabled; // reserved
    float hdrWhiteScale; // reserved
    float2 _padding;
    float4 vignetteColor; // Color of the vignette (usually black)
};

RWTexture2D<unorm float4> outputTexture : register(u0);

[numthreads(16, 16, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    uint width, height;
    outputTexture.GetDimensions(width, height);

    if (DTid.x >= width || DTid.y >= height)
        return;

    // Normalized texture coordinates (center of pixel)
    float2 texCoord = (float2(DTid.xy) + 0.5) / float2(width, height);

    // Sample the original texture
    float4 originalColor = outputTexture.Load(int3(DTid.xy, 0));

    // Adjust for aspect ratio
    float2 adjustedCoords = texCoord;
    if (screenAspect >= 1.0)
        adjustedCoords.y = (adjustedCoords.y - center.y) / screenAspect + center.y;
    else
        adjustedCoords.x = (adjustedCoords.x - center.x) / screenAspect + center.x;

    // Distance from center
    float2 distFromCenter = adjustedCoords - center;
    float dist = length(distFromCenter);

    // Smooth vignette falloff
    float vignetteFactor = smoothstep(radius, radius - smoothness, dist);

    // Apply intensity
    vignetteFactor = 1.0 - ((1.0 - vignetteFactor) * intensity);

    // Mix original color with vignette color
    float4 finalColor = lerp(vignetteColor, originalColor, vignetteFactor);

    // Contrast around 0.5 pivot
    finalColor.rgb = ((finalColor.rgb - 0.5f) * contrast) + 0.5f;

    // Saturation
    float luma = dot(finalColor.rgb, float3(0.2126f, 0.7152f, 0.0722f));
    finalColor.rgb = lerp(luma.xxx, finalColor.rgb, saturation);

    // Brightness
    finalColor.rgb *= brightness;

    // Lightweight pseudo-HDR boost for SDR output
    if (hdrBoost > 0.0f)
    {
        float3 boosted = finalColor.rgb / (1.0f + finalColor.rgb);
        finalColor.rgb = lerp(finalColor.rgb, boosted * (1.0f + hdrBoost), saturate(hdrBoost));
    }

    outputTexture[DTid.xy] = float4(saturate(finalColor.rgb), finalColor.a);
}
