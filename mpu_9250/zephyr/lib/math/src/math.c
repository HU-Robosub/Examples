float calculate_speed_xy(int x, float offset) {
    return x / offset;
}

float calculate_speed_z(int z, float offset) {
  return z / offset - offset;
}

int calculate_rotation(int x) {
    return x / 250;
}

// Get this value on init, when device is not moving
float get_offset(int z, float gravity) {
  return z / gravity;
}