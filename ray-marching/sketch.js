let caster;
const casterArea = 1;

let rays = [];
let totalRays = 1;

let obstacles = [];
let totalObstacles = 10;

// colors:
const colors = {
  background: [51],
  obstacle: {
    fill: [0, 100],
    stroke: [255],
  },
  caster: {
    fill: [255, 100],
  },
  ray: {
    stroke: [255, 200],
  },
  projection: {
    stroke: [255, 50],
  },
};

function getSignedDist(pos1, pos2, rad1, rad2, isSquare) {
  if (!isSquare) {
    return dist(pos1.x, pos1.y, pos2.x, pos2.y) - rad1 - rad2;
  }

  // FOR SQUARE:
  let { x: Px, y: Py } = pos1;
  let { x: Cx, y: Cy } = pos2;
  // Calculate the distance from the point to the center of the square
  const dx = Math.abs(Px - Cx) - rad1 - rad2;
  const dy = Math.abs(Py - Cy) - rad1 - rad2;

  // Check if the point is inside or outside the square
  if (dx <= 0 && dy <= 0) {
    // Point is inside the square
    return Math.max(dx, dy);
  } else if (dx > 0 && dy <= 0) {
    // Point is horizontally outside the square
    return dx;
  } else if (dx <= 0 && dy > 0) {
    // Point is vertically outside the square
    return dy;
  } else {
    // Point is diagonally outside the square
    return Math.sqrt(dx ** 2 + dy ** 2);
  }
}

function setup() {
  createCanvas(800, 600);
  background(...colors.background);

  caster = new Caster({
    pos: { x: width / 2, y: height / 2 },
    radius: 16,
    isFilled: true,
  });

  // cast rays:
  for (let i = 0; i < totalRays; i++) {
    let projection = new Projection({
      pos: { ...caster.pos },
      radius: 99999,
    });
    let velX = random(-1, 1);
    let velY = random(-1, 1);

    rays.push(
      new Ray({
        pos: { x: caster.pos.x, y: caster.pos.y },
        vel: { x: velX, y: velY },
        radius: 0.1,
        projection,
      })
    );
  }

  // spawn obstacles:
  for (let i = 0; i < totalObstacles; i++) {
    let x = random(0, width);
    let y = random(0, height);
    let radius = random(30, 50);
    let isSquare = random([true, false]);

    let signedDist = getSignedDist(
      { ...caster.pos },
      { x, y },
      caster.radius,
      radius,
      isSquare
    );

    while (signedDist < casterArea) {
      x = random(0, width);
      y = random(0, height);
      radius = random(30, 50);

      signedDist = getSignedDist(
        { ...caster.pos },
        { x, y },
        caster.radius,
        radius,
        isSquare
      );
    }

    let o = new Obstacle({
      pos: { x, y },
      radius: isSquare && radius > 50 ? radius * 0.75 : radius,
      isSquare,
    });
    obstacles.push(o);
  }

  // // draw obstacles:
  for (let obstacle of obstacles) {
    obstacle.draw();
  }
}

function draw() {
  // background(...colors.background);

  // draw obstacles:
  // for (let obstacle of obstacles) {
  //   obstacle.draw();
  // }

  // project & draw the rays:
  for (let ray of rays) {
    let closest = obstacles[0];
    let signedDistClosest = getSignedDist(
      { ...ray.pos },
      { ...closest.pos },
      ray.radius,
      closest.radius,
      closest.isSquare
    );

    if (
      ray.pos.x <= width &&
      ray.pos.x >= 0 &&
      ray.pos.y <= height &&
      ray.pos.y >= 0 &&
      signedDistClosest >= 0
    ) {
      // ray.noProjection();
      // ray.noRay();
      ray.draw();
    }

    for (let i = 0; i < 5; i++) {
      // find out the closest obstacle:
      for (let obstacle of obstacles) {
        let signedDist = getSignedDist(
          { ...ray.pos },
          { ...obstacle.pos },
          ray.radius,
          obstacle.radius,
          obstacle.isSquare
        );

        if (signedDist < signedDistClosest) {
          closest = obstacle;
          signedDistClosest = signedDist;
        }
      }

      // update projection & ray:
      if (
        ray.pos.x <= width &&
        ray.pos.x >= 0 &&
        ray.pos.y <= height &&
        ray.pos.y >= 0 &&
        signedDistClosest >= 0
      ) {
        ray.projection.update(ray.pos.x, ray.pos.y, signedDistClosest);
        ray.update();
      }
    }
  }

  // draw caster:
  caster.draw();
}
