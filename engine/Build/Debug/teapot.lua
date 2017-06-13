counter = 0;
function update(self, game)
    val = math.sin(counter);
    scale = Vector3.new(0.01, 0.01, 0.01);
    self:getTransform():setScale(scale)
    self:getTransform():setTranslateX(2.0);
    self:getTransform():setTranslateZ(2.0);
--    self:getTransform():setTranslateY(math.abs(val));
    self:getTransform():setRotateY(counter);
    counter = counter + 0.05 * game:getDelta();
end