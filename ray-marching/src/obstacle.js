class Obstacle {
  constructor({ pos, radius, isSquare }) {
    this.pos = { ...pos };
    this.radius = radius;
    this.isSquare = isSquare;
  }

  draw() {
    fill(...colors.obstacle.fill);
    stroke(...colors.obstacle.stroke);
    strokeWeight(2);
    noStroke();

    if (this.isSquare) {
      rectMode(RADIUS);
      rect(this.pos.x, this.pos.y, this.radius, this.radius);
    } else {
      ellipse(this.pos.x, this.pos.y, this.radius * 2);
    }
  }
}
