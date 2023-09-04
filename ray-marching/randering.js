let casters = [];
const totalCasters = 200;
const totalRays = 10;

let obstacles = [];
const totalObstacles = 5;

// colors:
const colors = {
  background: [255],
  obstacle: {
    fill: [255, 100],
    stroke: [255],
  },
  caster: {
    fill: [0, 100],
  },
  ray: {
    stroke: [0, 200],
  },
  projection: {
    stroke: [0, 5],
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

  // spawn random obstacle:
  for (let i = 0; i < totalObstacles; i++) {
    let x = random(0, width);
    let y = random(0, height);
    let radius = random(50, 100);
    let isSquare = random([true, false]);

    let obstacle = new Obstacle({
      pos: { x, y },
      radius: isSquare && radius > 75 ? radius * 0.75 : radius,
      isSquare,
    });

    obstacles.push(obstacle);
  }

  // spawn caster:
  for (let i = 0; i < totalCasters; i++) {
    let x = random(0, width);
    let y = random(0, height);
    let radius = 16;
    let isFilled = true;

    caster = new Caster({
      pos: { x, y },
      radius,
      isFilled,
    });

    // cast rays:
    let rays = [];
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

    casters.push({ caster, rays });
  }

  // draw obstacles:
  for (let obstacle of obstacles) {
    obstacle.draw();
  }
}

function draw() {
  // background(...colors.background);

  // draw obstacles:
  //   obstacle.draw();

  // project & draw the rays:
  for (let { caster, rays } of casters) {
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
        ray.noProjection();
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
    // caster.draw();
  }
}
