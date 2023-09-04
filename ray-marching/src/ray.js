class Ray {
  constructor({ pos, vel, radius, projection }) {
    this.pos = { ...pos };
    this.vel = { ...vel };
    this.prevPos = { ...this.pos };
    this.radius = radius;
    this.projection = projection;
    this.drawProjection = true;
    this.drawRay = true;
  }

  update() {
    this.pos.x += this.vel.x;
    this.pos.y += this.vel.y;
  }

  noProjection() {
    this.drawProjection = false;
  }

  noRay() {
    this.drawRay = false;
  }

  draw() {
    // draw projection:
    if (this.drawProjection) {
      this.projection.draw();
    }

    if (this.drawRay) {
      stroke(...colors.ray.stroke);
      strokeWeight(1);
      line(this.prevPos.x, this.prevPos.y, this.pos.x, this.pos.y);
      strokeWeight(1);
    }
  }
}
