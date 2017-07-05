counter = 0;
function update(self)
    val = math.sin(counter) * 10;
    scale = Vector3.new(0.01, 0.01, 0.01);
    self:getTransform():setScale(scale)
    --self:getTransform():setTranslateX(2.0);
    --self:getTransform():setTranslateZ(2.0);
    --self:getTransform():setTranslateY(math.abs(val));
    self:getTransform():setRotateY(counter);
    self:getTransform():setTranslateY(math.abs(val)* 0.05);
    counter = counter + 0.05 * STGame:Get():getDelta();
end

--[@Function Call]
function onHit(self, other)
    print("Linking OnHit");
end