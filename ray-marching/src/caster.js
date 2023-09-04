class Caster {
  constructor({ pos, radius, isFilled = false }) {
    this.pos = { ...pos };
    this.radius = radius;
    this.isFilled = isFilled;
  }

  draw() {
    fill(...colors.caster.fill);
    noStroke();
    if (!this.isFilled) {
      noFill();
    }
    ellipse(this.pos.x, this.pos.y, this.radius * 2);
  }
}
