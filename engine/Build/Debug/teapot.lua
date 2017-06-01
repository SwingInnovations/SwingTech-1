counter = 0;
function update(self, game)
    val = math.sin(counter);
    self:getTransform():setTranslateY(math.abs(val));
    counter = counter + 0.005 * game:getDelta();
end