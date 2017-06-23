counter = 0;
function update(self, game)
    val = math.sin(counter);
    scale = Vector3.new(0.5, 0.5, 0.5);
    self:getTransform():setScale(scale)
    --self:getTransform():setTranslateX(2.0);
    --self:getTransform():setTranslateZ(2.0);
    self:getTransform():setTranslateY(math.abs(val));
    self:getTransform():setRotateY(counter);
    --self:getTransform():setTranslateY(2);
    counter = counter + 0.005 * game:getDelta();
end

--[@Function Call]
function onCustomEven(self, other, game)

end