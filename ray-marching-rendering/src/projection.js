class Projection {
  constructor({ pos, radius }) {
    this.pos = { ...pos };
    this.radius = radius;
  }

  update(x, y, rad) {
    this.pos = { x, y };
    this.radius = rad;
  }

  draw() {
    noFill();
    stroke(...colors.projection.stroke);
    ellipse(this.pos.x, this.pos.y, this.radius * 2);
  }
}
