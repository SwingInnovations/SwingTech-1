function update(self, game)
    scale = Vector3.new(0.01, 0.01, 0.01);
    self:getTransform():setScale(scale);
    self:getTransform():setTranslateZ(-5);
end