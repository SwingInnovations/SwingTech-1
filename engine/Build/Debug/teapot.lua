counter = 0;
function update(self)
    val = math.sin(counter) * 10;
    scale = Vector3.new(0.01, 0.01, 0.01);
    self:transform():setScale(scale);
    self:transform():setTranslateZ(300.0);
    self:transform():setRotationMode(RotationMode.Local);
    self:transform():setRotateY(counter);
    counter = counter + 0.05 * STGame:Get():getDelta();
end

--[@Function Call]
function onHit(self, other)
    print("Linking OnHit");
end