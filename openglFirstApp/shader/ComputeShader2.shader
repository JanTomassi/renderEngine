#version 430
layout(local_size_x = 1, local_size_y = 1) in;

layout(std430, binding = 0) buffer aln
{
    float variable_array[];
};

layout(std430, binding = 1) buffer aln2
{
    unsigned int variable_array2[];
};

void main() {
}